#ifndef __HELPERS_H__
#define __HELPERS_H__

/*
Interface for helper functions for Game of Life assignment for CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is already here!
Remember, this is a header file: there should be no function bodies here, only prototypes.
Modified by: Mason Abrell on 9/14/2023
Changelog: I added the headers of the kill and revive functions to the file
*/

#include <stdlib.h>

void print_initial(int field[], size_t size);

void print_generation(int field[], unsigned int gen, size_t size);

void kill(int currarr[], size_t i);

void revive(int currarr[], size_t i);

#endif
