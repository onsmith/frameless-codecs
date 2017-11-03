/**
 * Name: Framifier.cpp
 * Purpose: TODO
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

#include <cstdint>


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input-filename output-filename frame-width frame-height frames-per-second"
	       << endl;
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 6) {
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
	const int  frames_per_second = atoi(argv[5]);

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

	// Create emulator object
	FramedCameraEmulator emulator(
		input_file,
		output_file,
		frame_width,
		frame_height,
		frames_per_second
	);

	// Run emulator
	int frame_count = 0;
	while (input_file.good()) {
		frame_count++;
		cout
			<< "Emulating frame number "
			<< frame_count
			<< ".."
			<< endl;
		emulator.emulateFrame();
	}

	// Close files
	input_file.close();
	output_file.close();

	// All done
	cout << "Done! "
		<< frame_count
		<< " frames emulated."
		<< endl;
	getchar();
	return 0;
}
