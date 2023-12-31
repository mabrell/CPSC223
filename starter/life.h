#ifndef __LIFE_H__
#define __LIFE_H__

/*
Interface for Game of Life assignment in CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is already here!
Remember, this is a header file: there should be no function bodies here, only prototypes.
Modified by: Mason Abrell on 914 & 9/15
Changelog: I added the kill, revive, and evolution functions
*/

#include <stdbool.h>
#include <stdlib.h>

bool isAlive(int field[], size_t i, size_t size);

bool shouldDie(int field[], size_t i, size_t size);

void kill(int currarr[], size_t i);

void revive(int currarr[], size_t i);

void evolution(int refarr[], int currarr[], size_t size);

int transfer_to_arrays(int refarr[], int currarr[], size_t c, int init_integer);

#endif
