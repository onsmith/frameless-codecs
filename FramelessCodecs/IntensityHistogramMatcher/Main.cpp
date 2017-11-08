/**
 * Solution: FramelessCodecs
 * Project: IntensithHistogramMatcher
 * File: Main.cpp
 * Purpose: TODO
 */


#include "Cicdf.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

#include <cstdint>


typedef uint16_t data_value_t;
typedef uint32_t histogram_bin_t;

typedef Cicdf::intensity_t  intensity_t;
typedef Cicdf::percentage_t percentage_t;


/*
** Prints the program usage to the given output stream.
*/
void print_usage(ostream& stream, char* program_filename) {
	stream << "Usage: "
	       << program_filename
	       << " histogram-filename"
	       << " cicdf-filename"
	       << endl;
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Check number of passed command line arguments
	if (argc != 3) {
		cerr << "Incorrect number of arguments." << endl;
		print_usage(cerr, argv[0]);
		getchar();
		return 1;
	}

	// Parse command line arguments
	const char* const program_filename   = argv[0];
	const char* const histogram_filename = argv[1];
	const char* const cicdf_filename     = argv[2];

	// Open histogram file
	ifstream histogram_file;
	histogram_file.open(histogram_filename, ios::in);
	if (!histogram_file.is_open()) {
		cerr << "Could not open file: "
		     << histogram_filename
		     << endl;
		getchar();
		return 1;
	}

	// Read histogram
	const size_t histogram_size = 0x1 << (sizeof(data_value_t) * 8);
	vector<histogram_bin_t> histogram(histogram_size);
	for (int i = 0; i < histogram_size; i++) {
		histogram_file >> histogram[i];
	}

	// Close histogram file
	histogram_file.close();

	// Convert histogram to cdf
	vector<double> cdf(histogram_size);
	cdf[0] = histogram[0];
	for (int i = 1; i < histogram_size; i++) {
		cdf[i] = cdf[i-1] + histogram[i];
	}
	const histogram_bin_t largest_cdf_bin = cdf[histogram_size - 1];
	for (int i = 0; i < histogram_size; i++) {
		cdf[i] = cdf[i] / largest_cdf_bin;
	}

	// Open cicdf file
	ifstream cicdf_file;
	cicdf_file.open(cicdf_filename, ios::in);
	if (!cicdf_file.is_open()) {
		cerr << "Could not open file: "
		     << cicdf_filename
		     << endl;
		getchar();
		return 1;
	}

	// Read continuous intensity cdf
	Cicdf cicdf;
	intensity_t  low_i, high_i = cicdf.intensityMin;
	percentage_t low_p, high_p = cicdf.percentageMin;
	while (cicdf_file >> low_i) {
		cicdf_file >> high_i >> low_p >> high_p;
		cicdf.addRegion(low_i, high_i, low_p, high_p);
	}
	if (high_i < cicdf.intensityMax || high_p < cicdf.percentageMax) {
		cicdf.addRegion(high_i, cicdf.intensityMax, high_p, cicdf.percentageMax);
	}

	// Close cicdf file
	cicdf_file.close();

	// Perform histogram matching
	vector<intensity_t> intensity_map(histogram_size);
	for (int i = 0; i < histogram_size; i++) {
		intensity_map[i] = cicdf.intensityAt(cdf[i]);
	}

	// Output results 
	for (int i = 0; i < histogram_size; i++) {
		printf("%.70lf\n", intensity_map[i]);
	}

	// All done
	return 0;
}
