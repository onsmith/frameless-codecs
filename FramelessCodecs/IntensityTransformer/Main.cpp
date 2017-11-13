/**
 * Solution: FramelessCodecs
 * Project: IntensityTransformer
 * File: Main.cpp
 * Purpose: TODO
 */


#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

#include <cstdint>


#define BUFFER_SIZE 640*360


typedef uint16_t input_value_t;
typedef double   output_value_t;


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input-filename"
	       << " output-filename"
	       << " map-filename"
	       << endl;
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 4) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cerr, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char* const program_filename = argv[0];
	const char* const input_filename   = argv[1];
	const char* const output_filename  = argv[2];
	const char* const map_filename     = argv[3];

	// Allocate mapping array
	const size_t map_size = 0x1 << (sizeof(input_value_t) * 8);
	vector<output_value_t> map(map_size);

	// Open map file
	ifstream map_file;
	map_file.open(map_filename, ios::in);
	if (!map_file.is_open()) {
		cerr << "Could not open file: "
		     << map_filename
		     << endl;
		getchar();
		return 1;
	}

	// Load map from file into memory
	for (int i = 0; i < map_size; i++) {
		map_file >> map[i];
	}

	// Close map file
	map_file.close();

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
	output_file.open(output_filename, ios::out | ios::binary);
	if (!output_file.is_open()) {
		cerr << "Could not open file: "
		     << output_filename
		     << endl;
		getchar();
		return 1;
	}

	// Loop through frames and apply mapping
	vector<input_value_t>   input_buffer(BUFFER_SIZE);
	vector<output_value_t> output_buffer(BUFFER_SIZE);
	while (input_file.good() && output_file.good()) {
		input_file.read(reinterpret_cast<char*>(input_buffer.data()), input_buffer.size()*sizeof(input_value_t));
		int n = input_file.gcount() / sizeof(input_value_t);
		for (int i = 0; i < n; i++) {
			output_buffer[i] = map[input_buffer[i]];
		}
		output_file.write(reinterpret_cast<char*>(output_buffer.data()), n*sizeof(output_value_t));
	}

	// Close files
	input_file.close();
	output_file.close();

	// All done
	return 0;
}
