#include "TextureConverter.h"
#include <Windows.h>

using namespace DirectX;

TexureConverter::TexureConverter() {
}

TexureConverter::~TexureConverter() {
}

void TexureConverter::ConvertTextureWICToDDS(const std::string& filepath) {
	LoadWICTextureFromFile(filepath);
	SaveDDSTextureToFile();
}

std::wstring TexureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {
	if (mString.empty()) {
		return std::wstring();
	}

	int sizeNeeded = MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<const char*>(&mString[0]), static_cast<int>(mString.size()), NULL, 0);
	if (sizeNeeded == 0) {
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<const char*>(&mString[0]), static_cast<int>(mString.size()), &result[0], sizeNeeded);
	return result;
}

void TexureConverter::LoadWICTextureFromFile(const std::string& filepath) {
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filepath);

	HRESULT result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));

	SeparateFilePath(wfilePath);
}

void TexureConverter::SeparateFilePath(const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;

	pos1 = filePath.rfind('.');
	// 検索ヒットなら
	if (pos1 != std::wstring::npos) {
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		exceptExt = filePath.substr(0, pos1);
	} else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TexureConverter::SaveDDSTextureToFile() {
	ScratchImage mipChain;
	HRESULT result;
	result = GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL,
		1.0f, converted);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	metadata_.format = MakeSRGB(metadata_.format);

	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
