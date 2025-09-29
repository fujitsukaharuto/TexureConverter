#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <Windows.h>

#include "TextureConverter.h"


enum Argument {
	kApplicationPath,
	kFilePath,

	NumArgument
};

int main(int argc, char* argv[]) {
	assert(argc >= NumArgument);
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TexureConverter converter;
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	for (int i = 0; i < argc; i++) {
		printf(argv[i]);
		printf("\n");
	}

	CoUninitialize();

	system("pause");
	return 0;
}