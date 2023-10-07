#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: Mason Abrell
*/

//Checks that the correct number of inputs were inputted
bool validity_check_a( int argc);


//Checks that the input file is accessible
bool validity_check_b(char* file_name);

//One function combining all validity checks and outputing whether
//the inputs are valid (true), or invalid (false)
bool big_validity_check (int argc, char* file_name);

#endif