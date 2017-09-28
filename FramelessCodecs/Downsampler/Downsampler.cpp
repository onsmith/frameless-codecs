/**
 * Name: Downsampler.cpp
 * Purpose: Downsamples a raw video file encoded in gray16le format, producing
 *   a new gray16le video file with half the vertical and horizontal
 *   resolution. Adds adjacent pixel intensities together when performing
 *   downsampling without regard for overflow.
 */


#include <iostream>
#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;


/*
** Prints the program usage to the standard output stream.
*/
void cout_usage(char* program_filename) {
	cout << "Usage: "
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
		cout_usage(argv[0]);
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

	// Downsample file

	// Close files
	input_file.close();
	output_file.close();

	// All done
	return 0;
}
