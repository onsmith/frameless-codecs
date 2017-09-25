#ifndef FRAME_H
#define FRAME_H


#include "stdio.h"


/*
** Internal routine to get the size of a given (open) file in bytes.
*/
long int fsize(FILE* file);


/*
** Internal routine to allocate sufficient memory and read a given number of
**   bytes from a given file.
*/
void* read_from_file(FILE* file, size_t num_bytes);


/*
** Internal routine to allocate sufficient memory and read an entire file into
**   memory.
*/
void* read_entire_file(FILE* file);


#endif
