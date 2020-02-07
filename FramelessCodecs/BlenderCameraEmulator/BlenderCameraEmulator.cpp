// BlenderCameraEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define TINYEXR_IMPLEMENTATION
#define TINYEXR_USE_THREAD 1
#include "tinyexr.h" // https://github.com/syoyo/tinyexr
#include "EventPixel.h"
int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";

	const char *program_filename = argv[0];
	const char *input_directory = argv[1];
	std::cout << input_directory <<"\n";
	std::string frame = input_directory;
	frame = frame + "\\frame_0001.exr";
	//const char* input = "C:\\Users\\AcFre\\Documents\\Blender Frames\\frame_0001.exr";
	const char* input = frame.c_str();
	std::cout << input << "\n";
	float* out; // width * height * RGBA
	int width;
	int height;
	//const char* err = NULL; // or nullptr in C++11

	//int ret = LoadEXR(&out, &width, &height, input, &err);

	//if (ret != TINYEXR_SUCCESS) {
	//	if (err) {
	//		fprintf(stderr, "ERR : %s\n", err);
	//		FreeEXRErrorMessage(err); // release memory of error message.
	//	}
	//}
	//else {
	//	printf("Successful read\n");
	//	printf("out[0]= %f\n", out[0]);
	//	EventPixel px(0, 0);
	//	px.integrate(out[0]);
	//	printf("%f\n", px.current_integration);
	//	free(out); // relase memory of image data
	//}




	// 1. Read EXR version.
	EXRVersion exr_version;

	int ret = ParseEXRVersionFromFile(&exr_version, input);
	if (ret != 0) {
		fprintf(stderr, "Invalid EXR file: %s\n", input);
		return -1;
	}

	if (exr_version.multipart) {
		// must be multipart flag is false.
		return -1;
	}

	// 2. Read EXR header
	EXRHeader exr_header;
	InitEXRHeader(&exr_header);

	const char* err = NULL; // or `nullptr` in C++11 or later.
	ret = ParseEXRHeaderFromFile(&exr_header, &exr_version, input, &err);
	if (ret != 0) {
		fprintf(stderr, "Parse EXR err: %s\n", err);
		FreeEXRErrorMessage(err); // free's buffer for an error message 
		return ret;
	}

	// // Read HALF channel as FLOAT.
	// for (int i = 0; i < exr_header.num_channels; i++) {
	//   if (exr_header.pixel_types[i] == TINYEXR_PIXELTYPE_HALF) {
	//     exr_header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT;
	//   }
	// }

	EXRImage exr_image;
	InitEXRImage(&exr_image);

	ret = LoadEXRImageFromFile(&exr_image, &exr_header, input, &err);
	if (ret != 0) {
		fprintf(stderr, "Load EXR err: %s\n", err);
		FreeEXRHeader(&exr_header);
		FreeEXRErrorMessage(err); // free's buffer for an error message 
		return ret;
	}

	// 3. Access image data
	width = exr_image.width;
	height = exr_image.height;
	EventPixel px(0, 0);
	px.integrate(exr_image.images[0][0]);
	printf("%f\n", px.current_integration);
	printf("%f\n", exr_image.images[0][0]);	//doing it this way returns normalized integer values, not floats!
	// `exr_image.images` will be filled when EXR is scanline format.
	// `exr_image.tiled` will be filled when EXR is tiled format.

	// 4. Free image data
	FreeEXRImage(&exr_image);
	FreeEXRHeader(&exr_header);
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
