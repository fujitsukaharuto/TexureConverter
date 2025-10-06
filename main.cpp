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
	if (argc < NumArgument) {
		TexureConverter::OutputUsage();
		return 0;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TexureConverter converter;

	int numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	for (int i = 0; i < argc; i++) {
		printf(argv[i]);
		printf("\n");
	}

	CoUninitialize();

	/*system("pause");*/
	return 0;
}