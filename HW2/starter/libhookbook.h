#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pirate.h"
#include "pirate_list.h"
/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: [your name here]
*/
//These functions check whether the input is valid, returning true if valid 
//and false if invalid
bool validity_check_a(int argc);

bool validity_check_b(char* file_name);

pirate_list* read_file_and_store(FILE *file_pointer);


#endif