/**
 * Solution: FramelessCodecs
 * Project: IntensityCombiner
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


typedef uint8_t intensity_t;


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " input1-filename"
	       << " input2-filename"
	       << " output-filename"
	       << " add-or-subtract"
	       << endl;
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 5) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cerr, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char* const program_filename = argv[0];
	const char* const input1_filename  = argv[1];
	const char* const input2_filename  = argv[2];
	const char* const output_filename  = argv[3];
	const char* const add_or_subtract  = argv[4];

	// Validate add or subtract
	const bool add      = (strcmp(add_or_subtract, "add"     ) == 0);
	const bool subtract = (strcmp(add_or_subtract, "subtract") == 0);
  if (!add && !subtract) {
		cerr << "Invalid option: "
		     << add_or_subtract
		     << endl;
		getchar();
		return 1;
	}


	// Open input file #1
	ifstream input1_file;
	input1_file.open(input1_filename, ios::in | ios::binary);
	if (!input1_file.is_open()) {
		cerr << "Could not open file: "
		     << input1_filename
		     << endl;
		getchar();
		return 1;
	}

	// Open input file #2
	ifstream input2_file;
	input2_file.open(input2_filename, ios::in | ios::binary);
	if (!input2_file.is_open()) {
		cerr << "Could not open file: "
		     << input2_filename
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

	// Loop through frames and add signals
	vector<intensity_t> input1_buffer(BUFFER_SIZE);
	vector<intensity_t> input2_buffer(BUFFER_SIZE);
	vector<intensity_t> output_buffer(BUFFER_SIZE);
	while (input1_file.good() && input2_file.good() && output_file.good()) {
		input1_file.read(reinterpret_cast<char*>(input1_buffer.data()), input1_buffer.size()*sizeof(intensity_t));
		input2_file.read(reinterpret_cast<char*>(input2_buffer.data()), input2_buffer.size()*sizeof(intensity_t));
		int n = (input1_file.gcount() < input2_file.gcount()) ? input1_file.gcount() : input2_file.gcount();
		n /= sizeof(intensity_t);
		if (add) {
			for (int i = 0; i < n; i++) {
				output_buffer[i] = input1_buffer[i] + input2_buffer[i];
			}
		} else {
			for (int i = 0; i < n; i++) {
				output_buffer[i] = input1_buffer[i] - input2_buffer[i];
			}
		}
		output_file.write(reinterpret_cast<char*>(output_buffer.data()), n*sizeof(intensity_t));
	}

	// Close files
	input1_file.close();
	input2_file.close();
	output_file.close();

	// All done
	return 0;
}
