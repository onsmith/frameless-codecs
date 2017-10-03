/**
 * Name: Downsampler.cpp
 * Purpose: Downsamples a raw video file encoded in gray16le format, producing
 *   a new gray16le video file with half the vertical and horizontal
 *   resolution. Adds adjacent pixel intensities together when performing
 *   downsampling without regard for overflow.
 */


#include <iostream>
#include <fstream>
#include <cstdint>

#include "MonoFrame.h"
//#include "YUV444pFrame.h"
//#include "YUV422pFrame.h"
//#include "YUV420pFrame.h"


using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;


#define PRINT_UPDATE_EVERY_X_FRAMES 30


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input-filename output-filename input-frame-width input-frame-height"
	       << endl;
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 5) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cout, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char *program_filename  = argv[0];
	const char *input_filename    = argv[1];
	const char *output_filename   = argv[2];
	const int  input_frame_width  = atoi(argv[3]);
	const int  input_frame_height = atoi(argv[4]);


	// Validate frame dimensions
	if (input_frame_width <= 0 || input_frame_height <= 0) {
		cerr << "Invalid frame dimensions: "
		     << input_frame_width
		     << 'x'
		     << input_frame_height
		     << endl;
		getchar();
		return 1;
	}

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
	MonoFrame<uint16_t>  input_frame(input_frame_width,   input_frame_height  );
	MonoFrame<uint16_t> output_frame(input_frame_width/2, input_frame_height/2);

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
