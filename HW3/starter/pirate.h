#ifndef __PIRATE_H__
#define __PIRATE_H__
#include "skills_list.h"
#include <stdbool.h>
#include <stdio.h>

/*
Header file for pirate for assignment HookBook assignments in CPSC 223 FA2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is
    already here!
Modified by: [your name here] on [date of modification]
Changelog: [what you added to this file]
*/

/**
 * Type of a pirate
 */
typedef struct suspicious_pirate pirate;

/**
 * Allocates enough memory for a pirate, and returns a pointer to the newly-
 *  allocated memory.
 */
pirate *pirate_create(void);

/**
 * Reads a pirate profile from input. If the file cursor is not at the
 *  beginning of a pirate profile, this function returns NULL.
 *
 * Returns a pointer to a pirate created from the profile in input.
 *
 * This function consumes a blank line after the end of the current profile
 *  before returning, meaning that after this function is done, the input
 *  cursor is either at the end of the input file or at the beginning of the
 *  next pirate profile.
 */
pirate *pirate_read(FILE *restrict input);

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 */
void pirate_print(const pirate *p, FILE *restrict output);

/**
 * Returns the name of the pirate.
 */
const char *pirate_name(const pirate *p);

/**
 * Sets the name of a pirate.
 */
void pirate_set_name(pirate *p, const char *name);

/**
 * Returns the vessel of the pirate.
 */
const char *pirate_vessel(const pirate *p);

/**
 * Sets the vessel of a pirate.
 */
void pirate_set_vessel(pirate *p, const char *vessel);

/**
 * Returns the favorite port of call of the pirate.
 */
const char *pirate_port(const pirate *p);

/**
 * Sets the favorite port of call of a pirate.
 */
void pirate_set_port(pirate *p, const char *port);

/**
 * Returns the rank of the pirate.
 */
const char *pirate_rank(const pirate *p);

/**
 * Sets the rank of a pirate.
 */
void pirate_set_rank(pirate *p, const char *rank);

/**
 * Returns the treasure of the pirate.
 */
unsigned int pirate_treasure(const pirate *p);

/**
 * Sets the treasure of a pirate.
 */
void pirate_set_treasure(pirate *p, unsigned int treasure);

/**
 * Returns a pointer to the profile of the pirate's captain.
 */
const pirate *pirate_captain(const pirate *p);

/**
 * Sets the captain of a pirate.
 */
void pirate_set_captain(pirate *p, const pirate *cpt);

/**
 * Returns a pointer to the list of skills of the pirate.
 */
skills_list *pirate_skills(const pirate *p);

/**
 * Frees all memory associated with this pirate. This function claims ownership
 *  of p.
 */
void pirate_destroy(pirate *p);

//copies what is after the colon in a string that gets returned
//stands for "post-colon-copy"
char* pcc(char* input);


//Returns the size of the pirate struct
size_t get_pirate_size();


//getter for treasure_change
bool get_treasure_change(pirate* jack);

//getter for vessel_change
bool get_vessel_change(pirate* jack);

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 */
int pirate_compare(pirate *a, pirate *b);

//sets captain changed
void set_captain_changed(pirate* p, bool value);

//gets captain changed
bool get_captain_changed(pirate* p);


#endif
