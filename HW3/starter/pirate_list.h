#include <stdbool.h>

#ifndef __PIRATE_LIST_H__
#define __PIRATE_LIST_H__

/*
Header file for pirate list for Hookbook assignments for CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is
    already here!
Modified by: [your name here] on [date of modification]
Changelog: [what you added to this file]
*/

#include <stdlib.h>

#include "pirate.h"

/**
 * Type of a list of pirates, as an opaque struct.
 */
typedef struct pirate_list_instance_t pirate_list;

/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 *
 * The comparison function returns a negative number, zero, or a positive number
 *  as the first argument "comes before", is the same as, or "comes after" the
 *  second.
 */
pirate_list *list_create(int (*comp)(const void *, const void *));



/**
 * Return the index of the pirate with the same name as p, or a value greater
 *  than or equal to the length of the list if the pirate is not in the list.
 *
 * Ownership of p is not changed.
 */
size_t list_index_of(pirate_list *pirates, pirate *p);

//Sorts pirates' pirate_array lexographically, given a low and a high
void quicksort(pirate_list *pirates, int low, int high);


// //function for function pointer - compares two pirates via name. Works similar
// //to strcmp, but intaking pirate profiles
// int name_comp(pirate* argh1, pirate* argh2);


// //Another function for function pointer, compares via vessel lexicographically
// int vessel_comp(pirate* argh1, pirate* argh2);

// //Another function for function pointer, compares via treasure, descending 
// int vessel_comp(pirate* argh1, pirate* argh2);

//Returns True if pirate exists in the pirate_list, false if not
bool pirate_existence(pirate_list *pirates, const char* name);


//Given a pirate name, will find its corresponding index if its in the list
size_t nti(pirate_list *pirates, char* name);


/**
 * Only if there is no pirate in the list with the same name as p, insert
 *  pirate p into the list at index idx by copying the pointer, shifting the
 *  latter part of the list one "slot" to the right.
 *
 * Assumes 0 <= idx <= [the length of the list] (otherwise its behavior is
 *  undefined).
 *
 * If there is a pirate in the list with the same name as p, do nothing, and
 *  return p (the pirate that was not inserted).
 *
 * If the pirate was inserted into the list, return NULL.
 *
 * If p is added to the list, the list claims ownership of the pirate pointed
 *  to by p; otherwise ownership remains with p.
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

/**
 * Remove the pirate from the list with the same name as p, and return a
 *  pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL.
 *
 * The caller of this function is responsible for freeing the returned pirate
 *   if it is not NULL.
 */
pirate *list_remove(pirate_list *pirates, pirate *p);

/**
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL
 *  if idx is not a valid index (i.e., it is >= the length of the list).
 *
 * Ownership of the pirate remains with the list.
 */
pirate *list_access(pirate_list *pirates, size_t idx);

//Getter for pirate_list capacity
size_t get_capacity_value(pirate_list* pirates);


/**
 * Sort the list of pirates according to the order defined when this list was
 * created.
 */
void list_sort(pirate_list *pirates);

/**
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates);

/**
 * Free all memory associated with the list, including the pirates in the list.
 */
void list_destroy(pirate_list *pirates);

//Swaps the index of two pirates in a chosen pirate_list
void swap(pirate_list* pirate_list_instance,size_t idxa, size_t idxb);

//To be used right before you add a pirate, expands list if necessary
void list_expand_if_necessary(pirate_list *pirates);

//To be used right before you add a pirate, contracts list if necessary
void list_contract_if_necessary(pirate_list *pirates);

//Sorts pirate_list so that no treasure pirates are at the end
size_t no_treasure_to_end(pirate_list* pirates);

//Same thing as above, but for pirates that don't have a vessel
size_t no_vessel_to_end(pirate_list* pirates);

//Reads through captain file and adds captains to each pirate
void captain_read(pirate_list* pirates, FILE *restrict input);

//getter for sort_type
char get_sort_type(pirate_list* pirates);

//setter for sort_type
void set_sort_type(pirate_list* pirates, char input);

#endif
