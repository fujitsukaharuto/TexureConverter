#pragma once
#include <string>

class TexureConverter {
public:
	TexureConverter();
	~TexureConverter();

	void ConvertTextureWICToDDS(const std::string& filepath);

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
	void LoadWICTextureFromFile(const std::string& filepath);
};
