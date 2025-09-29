#include "TextureConverter.h"
#include <Windows.h>

TexureConverter::TexureConverter() {
}

TexureConverter::~TexureConverter() {
}

void TexureConverter::ConvertTextureWICToDDS(const std::string& filepath) {

	LoadWICTextureFromFile(filepath);

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

}
