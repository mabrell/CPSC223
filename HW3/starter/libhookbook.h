#include "pirate_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>



#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h, pirate_list.h, or skills_list.h.

Author: [your name here]
*/
bool argc_validity_check(int argc);

bool argc3_validity_check(char* argv1, char* argv2);

bool argc4_validity_check(char* argv1, char* argv2, char* argv3);

bool validity_check_b(char* file_name);

//This processes the command line arguements for a 4argc input, and returns a
//correspondingly created pirate pointer
pirate_list* argc4_prcs_pirate(char* argv1, char* argv2, char* argv3, int (*name_comp)(const void *, const void *), int (*treasure_comp)(const void *, const void *), int (*vessel_comp)(const void *, const void *));

//This returns the pointer to the pirate file for a 4argc input
FILE* argc4_prcs_pirate_file(char* argv1, char* argv2, char* argv3);

//This returns the pointer to the captain file for a 4argc input
FILE* argc4_prcs_captn_file(char* argv1, char* argv2, char* argv3);


//Returns the flag found in the input
char argc4_prcs_flag(char* argv1, char* argv2, char* argv3);

#endif