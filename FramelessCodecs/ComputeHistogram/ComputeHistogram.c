#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"


void printUsage(char *filename);


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *inputFilename;
	int frameWidth, frameHeight;
	if (argc == 4) {
		inputFilename = argv[1];
		frameWidth    = atoi(argv[2]);
		frameHeight   = atoi(argv[3]);
	} else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		printUsage(argv[0]);
		exit(1);
	}

	// Allocate histogram, tracking parameters
	int frameCount = 0;
	uint32_t *histogram = calloc((0x1 << 16), sizeof(uint32_t));

	// Open file, allocate buffer
	int frameSize = frameWidth*frameHeight;
	uint16_t *frame = malloc(frameSize * sizeof(uint16_t));
	FILE *inputFile = fopen(inputFilename, "rb");

	// Loop through file and accumulate histogram
	while (fread(frame, sizeof(*frame), frameSize, inputFile) == frameSize) {
		frameCount++;
		for (int i = 0; i < frameSize; i++) {
			histogram[frame[i]]++;
		}
	}

	// Close file
	fclose(inputFile);

	// Free frame memory
	free(frame);

	// Output results
	for (int i = 0; i < (0x1 << 16); i++) {
		printf("%i\n", histogram[i]);
	}
	fprintf("%i frames analyzed.\n", frameCount);

	// Free histogram memory
	free(histogram);

	// All done
	return 0;
}


/**
 * Prints the program usage to the standard output stream.
 */
void printUsage(char *filename) {
	printf("Usage: %s input-filename frame-width frame-height\n", filename);
}
