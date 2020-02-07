// BlenderCameraEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define TINYEXR_IMPLEMENTATION
#define TINYEXR_USE_THREAD 1
#include "tinyexr.h" // https://github.com/syoyo/tinyexr
int main()
{
    std::cout << "Hello World!\n";

	const char* input = "C:\\Users\\AcFre\\Documents\\Blender Frames\\frame_0001.exr";
	float* out; // width * height * RGBA
	int width;
	int height;
	const char* err = NULL; // or nullptr in C++11

	int ret = LoadEXR(&out, &width, &height, input, &err);

	if (ret != TINYEXR_SUCCESS) {
		if (err) {
			fprintf(stderr, "ERR : %s\n", err);
			FreeEXRErrorMessage(err); // release memory of error message.
		}
	}
	else {
		printf("Successful read\n");
		printf("out[0]= %f\n", out[0]);
		free(out); // relase memory of image data
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
