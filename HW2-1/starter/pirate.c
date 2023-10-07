#include "pirate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct suspicious_pirate { //I named it suspicious pirate bc they're hiding
                            //behind an opaque construct!
    char* name;
    //char* rank_name;
    //char* vessel_name;
    //char* port_name;
    //size_t treasure_amount;
    //char* skills;

};


//This function creates a pirate, allocating memory for the struct itself
pirate* pirate_create()
{
	pirate *new_p = malloc(sizeof(pirate));
	return new_p;
}


// /**
//  * Reads a pirate profile from input. Assumes that the input cursor is at the
//  *  beginning of a pirate profile (otherwise, its behavior is undefined).
//  *
//  * Returns a pointer to a pirate created from the profile in input.
//  *
//  * This function consumes a blank line after the end of the current profile
//  *  before returning, meaning that after this function is done, the input
//  *  cursor is either at the end of the input file or at the beginning of the
//  *  next pirate profile.
//  */

pirate *pirate_read(FILE *restrict input)
{
	pirate* new_pirate_pointer = pirate_create();
	bool found_a_pirate = false;
	while (!found_a_pirate)
	{
		bool newline = false;
		char* handover_pointer = malloc(128 * sizeof(char));
		handover_pointer = fgets(handover_pointer, 128, input);
		if (handover_pointer == NULL)
		{
			free(handover_pointer);
			free(new_pirate_pointer);
			found_a_pirate = false;
			return NULL;
		}
		if (handover_pointer[0] == '\n')
		{
			free(handover_pointer);
			newline = true;
		}
		if (newline == false)
		{
			pirate_set_name(new_pirate_pointer, handover_pointer);
			free(handover_pointer);
			return new_pirate_pointer;
		}
	}
	return NULL;
}


//returns the sizeof pirate
size_t get_pirate_size()
{
	return sizeof(pirate);
}


/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 */
void pirate_print(const pirate *p, FILE *restrict output)
{
    char* name = p->name;
    fprintf(output, "%s", name);
}

/**
 * Returns the name of the pirate.
 */
const char *pirate_name(const pirate *p)
{
	return p->name;
}

/**
 * Sets the name of a pirate.
*/
void pirate_set_name(pirate *p, const char* name)
{
	p->name = malloc(128 * sizeof(char));
	strcpy(p->name, name);
}

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 */
int pirate_compare(pirate *a, pirate *b)
{
	return strcmp(a->name, b->name);
}

/**
 * Frees all memory associated with this pirate. This function claims ownership
 *  of p.
 */
void pirate_destroy(pirate *p){
	free(p->name);
	free(p);
}

size_t pirate_size()
{
	return sizeof(pirate);
}