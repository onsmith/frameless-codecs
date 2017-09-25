#include "files.h"


long int fsize(FILE* file) {
	const long int initial_position = ftell(file);
	fseek(file, 0, SEEK_END);
	const long int fsize = ftell(file);
	fseek(file, initial_position, SEEK_SET);
	return fsize;
}


void* read_from_file(FILE* file, size_t num_bytes) {
	void *data = malloc(num_bytes);
	fread(data, 1, num_bytes, file);
	return data;
}


void* read_entire_file(FILE* file) {
	fseek(file, 0, SEEK_SET);
	return read_from_file(file, fsize(file));
}
