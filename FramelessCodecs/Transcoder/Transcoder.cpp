/**
 * Name: Transcoder.cpp
 * Purpose: Transcodes a given input raw video file, producing a new video file
 *   encoded in a different raw format.
 */


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <algorithm>
using std::copy;

#include <cstdint>

#include "Frame/MonoFrame.h"
#include "Frame/YUV420Frame.h"
#include "Frame/YUV422Frame.h"
#include "Frame/YUV444Frame.h"


#define PRINT_UPDATE_EVERY_X_FRAMES 30


/*
** Converts a yuv444p frame to a yuv422p frame.
*/
void yuv444p_to_yuv422p(YUV444Frame<uint8_t>& src, YUV422Frame<uint8_t>& dst) {
	const int num_pixels = src.width() * src.height();
	copy(src.y(), src.y() + num_pixels, dst.y());
	for (int i = 0; i < num_pixels / 2; i++) {
		dst.u(i) = src.u(2*i);
		dst.v(i) = src.v(2*i);
	}
}


/*
** Converts a yuv444p frame to a yuv420p frame.
*/
void yuv444p_to_yuv420p(YUV444Frame<uint8_t>& src, YUV420Frame<uint8_t>& dst) {
	const int num_pixels = src.width() * src.height();
	copy(src.y(), src.y() + num_pixels, dst.y());
	for (int y = 0; y < src.height() / 2; y++) {
		for (int x = 0; x < src.width() / 2; x++) {
			dst.u(x, y) = src.u(2*x, 2*y);
			dst.v(x, y) = src.v(2*x, 2*y);
		}
	}
}


/*
** Converts a yuv444p frame to a gray16le frame.
*/
void yuv444p_to_gray16le(YUV444Frame<uint8_t>& src, MonoFrame<uint16_t>& dst) {
	for (int i = 0; i < src.width() * src.height(); i++) {
		dst.intensityAt(i) = src.y(i) << 8;
	}
}


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input-filename output-filename frame-width frame-height input-format output-format"
	       << endl;
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 7) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cerr, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char *program_filename = argv[0];
	const char *input_filename   = argv[1];
	const char *output_filename  = argv[2];
	const int  frame_width       = atoi(argv[3]);
	const int  frame_height      = atoi(argv[4]);
	const char *input_format     = argv[5];
	const char *output_format    = argv[6];

	// Validate frame dimensions
	if (frame_width <= 0 || frame_height <= 0) {
		cerr << "Invalid frame dimensions: "
		     << frame_width
		     << 'x'
		     << frame_height
		     << endl;
		getchar();
		return 1;
	}

	// Allocate input frame


	// Open input file
	ifstream input_file;
	input_file.open(input_filename, ios::in | ios::binary);
	if (!input_file.is_open()) {
		cerr << "Could not open file: "
		     << input_filename
		     << endl;
		getchar();
		return 1;
	}

	// Open output file
	ofstream output_file;
	output_file.open(output_filename, ios::out | ios::binary | ios::trunc);
	if (!output_file.is_open()) {
		cerr << "Could not open file: "
		     << output_filename
		     << endl;
		getchar();
		return 1;
	}

	// Allocate frames
	//MonoFrame<uint16_t>  input_frame(input_frame_width,   input_frame_height  );
	//MonoFrame<uint16_t> output_frame(input_frame_width/2, input_frame_height/2);

	// Downsample file
	int frame_count = 0;
	while (input_frame.readFrom(input_file)) {
		frame_count++;
		if (frame_count % PRINT_UPDATE_EVERY_X_FRAMES == 0) {
			cout << "Downsampling frame number "
				<< frame_count
				<< ".."
				<< endl;
		}
		for (int y = 0; y < input_frame.height()/2; y++) {
			for (int x = 0; x < input_frame.width()/2; x++) {
				output_frame.intensityAt(x, y) =
					input_frame.intensityAt(2*x,   2*y  ) +
					input_frame.intensityAt(2*x+1, 2*y  ) +
					input_frame.intensityAt(2*x,   2*y+1) +
					input_frame.intensityAt(2*x+1, 2*y+1);
			}
		}
		output_frame.writeTo(output_file);
	}

	// Close files
	input_file.close();
	output_file.close();

	// All done
	cout << "Done! "
		<< frame_count
		<< " frames downsampled."
		<< endl;
	getchar();
	return 0;
}
