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

#include <cstdint>

#include "Frame/Gray16leFrame.h"
#include "Frame/GrayDoubleFrame.h"
#include "Frame/Yuv420pFrame.h"
#include "Frame/Yuv422pFrame.h"
#include "Frame/Yuv444pFrame.h"


#define PRINT_UPDATE_EVERY_X_FRAMES 30


/*
** Valid frame formats.
*/
enum class FrameFormat {
	Unknown,
	Gray16le,
	GrayDouble,
	Yuv444p,
	Yuv422p,
	Yuv420p,
};


/*
** Factory method for frame objects.
*/
Frame* CreateFrame(int width, int height, FrameFormat frame_format) {
	switch (frame_format) {
	case FrameFormat::Gray16le:
		return new Gray16leFrame(width, height);
	case FrameFormat::GrayDouble:
		return new GrayDoubleFrame(width, height);
	case FrameFormat::Yuv444p:
		return new Yuv444pFrame(width, height);
	case FrameFormat::Yuv422p:
		return new Yuv422pFrame(width, height);
	case FrameFormat::Yuv420p:
		return new Yuv420pFrame(width, height);
	default:
		return nullptr;
	}
}


/*
** Lookup function for a frame format.
*/
FrameFormat LookupFrameFormat(const char* const frame_format) {
	if (strcmp(frame_format, "gray16le") == 0) {
		return FrameFormat::Gray16le;
	} else if (strcmp(frame_format, "graydouble") == 0) {
		return FrameFormat::GrayDouble;
	} else if (strcmp(frame_format, "yuv444p") == 0) {
		return FrameFormat::Yuv444p;
	} else if (strcmp(frame_format, "yuv422p") == 0) {
		return FrameFormat::Yuv422p;
	} else if (strcmp(frame_format, "yuv420p") == 0) {
		return FrameFormat::Yuv420p;
	} else {
		return FrameFormat::Unknown;
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
	const char        *program_filename  = argv[0];
	const char        *input_filename    = argv[1];
	const char        *output_filename   = argv[2];
	const int         frame_width        = atoi(argv[3]);
	const int         frame_height       = atoi(argv[4]);
	const char        *input_format_str  = argv[5];
	const char        *output_format_str = argv[6];
	const FrameFormat input_format       = LookupFrameFormat(input_format_str);
	const FrameFormat output_format      = LookupFrameFormat(output_format_str);

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

	// Validate input frame format
	if (input_format == FrameFormat::Unknown) {
		cerr << "Invalid input frame format: "
		     << input_format_str
		     << endl
		     << "Valid options are: gray16le, graydouble, yuv444p, yuv422p, yuv420p"
		     << endl;
		getchar();
		return 1;
	}

	// Validate output frame format
	if (output_format == FrameFormat::Unknown) {
		cerr << "Invalid output frame format: "
		     << output_format_str
		     << endl
		     << "Valid options are: gray16le, graydouble, yuv444p, yuv422p, yuv420p"
		     << endl;
		getchar();
		return 1;
	}

	// Prepare function pointer to transcoding algorithm
	void (*TranscodeAlgorithm)(Frame& const input, Frame& const output);

	switch(input_format) {
	case (FrameFormat::Gray16le):
		switch(output_format) {
		case (FrameFormat::GrayDouble):
			TranscodeAlgorithm = [](Frame& const input, Frame& const output) {
				static_cast<GrayDoubleFrame&>(output) = static_cast<Gray16leFrame&>(input);
			};
			break;
		case (FrameFormat::Yuv444p):
			break;
		case (FrameFormat::Yuv422p):
			break;
		case (FrameFormat::Yuv420p):
			break;
		}
		break;
	case (FrameFormat::GrayDouble):
		switch(output_format) {
		case (FrameFormat::Gray16le):
			break;
		case (FrameFormat::Yuv444p):
			break;
		case (FrameFormat::Yuv422p):
			break;
		case (FrameFormat::Yuv420p):
			break;
		}
		break;
	case (FrameFormat::Yuv444p):
		switch(output_format) {
		case (FrameFormat::Gray16le):
			break;
		case (FrameFormat::GrayDouble):
			break;
		case (FrameFormat::Yuv422p):
			break;
		case (FrameFormat::Yuv420p):
			break;
		}
		break;
	case (FrameFormat::Yuv422p):
		switch(output_format) {
		case (FrameFormat::Gray16le):
			break;
		case (FrameFormat::GrayDouble):
			break;
		case (FrameFormat::Yuv444p):
			break;
		case (FrameFormat::Yuv420p):
			break;
		}
		break;
	case (FrameFormat::Yuv420p):
		switch(output_format) {
		case (FrameFormat::Gray16le):
			break;
		case (FrameFormat::GrayDouble):
			break;
		case (FrameFormat::Yuv444p):
			break;
		case (FrameFormat::Yuv422p):
			break;
		}
		break;
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

	// Allocate buffer frames
	Frame* input_frame  = CreateFrame(frame_width, frame_height, input_format);
	Frame* output_frame = CreateFrame(frame_width, frame_height, output_format);

	// Transcode video
	int frame_count = 0;
	while (input_frame->readFrom(input_file)) {
		frame_count++;
		if (frame_count % PRINT_UPDATE_EVERY_X_FRAMES == 0) {
			cout << "Downsampling frame number "
				<< frame_count
				<< ".."
				<< endl;
		}
		//*output_frame = *input_frame;
		TranscodeAlgorithm(*input_frame, *output_frame);
		output_frame->writeTo(output_file);
	}

	// Close files
	input_file.close();
	output_file.close();

	// Free memory
	delete input_frame;
	delete output_frame;

	// All done
	cout << "Done! "
		<< frame_count
		<< " frames downsampled."
		<< endl;
	getchar();
	return 0;
}
