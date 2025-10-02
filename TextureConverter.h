#pragma once
#include <string>

#include "externals/DirectXTex/DirectXTex.h"
#include "externals/DirectXTex/d3dx12.h"

class TexureConverter {
public:
	TexureConverter();
	~TexureConverter();

	void ConvertTextureWICToDDS(const std::string& filepath);

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
	void LoadWICTextureFromFile(const std::string& filepath);
	void SeparateFilePath(const std::wstring& filePath);
	void SaveDDSTextureToFile();

	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage scratchImage_;

	std::wstring directoryPath_;
	std::wstring fileName_;
	std::wstring fileExt_;
};
