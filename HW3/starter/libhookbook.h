#include "pirate_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>



#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h, pirate_list.h, or skills_list.h.

Author: Mason Abrell
*/
bool argc_validity_check(int argc);

bool argc3_validity_check(char* argv1, char* argv2);

bool argc4_validity_check(char* argv1, char* argv2, char* argv3);

bool validity_check_b(char* file_name);

//This processes the command line arguements for a 4argc input, and returns a
//correspondingly created pirate pointer
pirate_list* argc4_p(char* argv1, char* argv2, char* argv3, int (*name_comp)(const void *, const void *), int (*treasure_comp)(const void *, const void *), int (*vessel_comp)(const void *, const void *));

//This returns the pointer to the pirate file for a 4argc input
FILE* argc4_prcs_pirate_file(char* argv1, char* argv2, char* argv3);

//This returns the pointer to the captain file for a 4argc input
FILE* argc4_prcs_captn_file(char* argv1, char* argv2, char* argv3);


//Returns the flag found in the input
char argc4_prcs_flag(char* argv1, char* argv2, char* argv3);


//Refactoring of entire read and sort sequence
void pirate_read_and_sort(FILE* fptr, FILE* cpt, pirate_list* new_pirate_list);

//Prints the entire inputted pirate list
void print_whole_list(pirate_list* new_pirate_list);

//Closes files and destroys list
void clean_up(FILE* fptr, FILE* fptr_two, pirate_list* lst);

//Does a total validity check and returns 0 if all good, 1 if theres a prob
int total_validity_check(size_t argc,char* argv1, char* argv2, char* argv3);
#endif