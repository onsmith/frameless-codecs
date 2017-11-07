/**
 * Solution: FramelessCodecs
 * Project: IntensithHistogramMatcher
 * File: Main.cpp
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


typedef uint16_t data_value_t;
typedef uint32_t histogram_bin_t;


#define PRINT_UPDATE_EVERY_X_VALUES 1000


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input-filename"
	       << endl;
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 2) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cerr, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char* const program_filename = argv[0];
	const char* const input_filename   = argv[1];

	// Allocate histogram
	const size_t histogram_size = 0x1 << (sizeof(data_value_t) * 8);
	histogram_bin_t histogram[histogram_size] = {0};

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

	// Traverse file and accumulate histogram
	data_value_t buffer;
	input_file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
	while (input_file.good()) {
		histogram[buffer]++;
		input_file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
	}

	// Close file
	input_file.close();

	// Output results
	for (int i = 0; i < histogram_size; i++) {
		cout << histogram[i] << endl;
	}

	// All done
	return 0;
}
