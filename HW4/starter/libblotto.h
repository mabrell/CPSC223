#ifndef __LIBBLOTTO_H__
#define __LIBBLOTTO_H__

#include "gmap.h"
#include <stdio.h>
/**
 * Header File for blotto functions
 * Author: Mason Abrell
 * Pset 4
 * Date: 11/4/2023
 */

/**
 * Creates an empty blotto map that uses the functions corresponding to strings
 *
 * @return a pointer to the new map or NULL if it could not be created;
 * it is the caller's responsibility to destroy the map
 */
gmap* bmap_create();


/**
 * Takes two Player IDs, battlefield values, total number of battlefields, and 
 * the hash map m.
 * takes their distributions, calculates the results of a 
 * blotto match between them, then prints out the results in the correct format, 
 * returning nothing and leaving it to the caller to destroy the players in the 
 * has map.
 *
 * @param p_a a char* to the first player's id
 * @param p_b a char* to the second player's id
 * @param btl_num an integer denoting the number of battlefields
 * @param btl_valu a pointer to an integer array containing distributions
 * @param m pointer to the corresponding hash map
 */
void run_btl(char* p_a, char* p_b, size_t btl_num, int* btl_valu, gmap* m);


/**
 * Reads a single profile and distribution into the hash map
 *
 * @param in a pointer to the file
 * @param m a pointer to the hasmap
 * @param battlefields a size_t for the number of battlefields
 * @param a boolean detailing whether this is the first time the program has run
 * validly
 * @return integer corresponding to read state, -1 if continue as normal, -2 if 
 * end is reached, -3 if error/skip
 */
int read_profile(FILE *in, gmap* m, size_t battlefields, bool ft, int pt);

/**
 * Reads entire profiles section into the hash map
 *
 * @param in a pointer to the file
 * @param m a pointer to the hasmap
 * @param battlefields a size_t for the number of battlefields
 * @return int denoting if errors were detected
 */
int read_and_store(FILE *in, gmap* m, size_t battlefields);

/**
 * Reads entire pairings portion, runs each battle, prints result
 *
 * @param in a pointer to the file
 * @param m a pointer to the hasmap
 * @param btl_num a size_t for the number of battlefields
 * @param btl_valu an integer array detailing the battlefield point values.
 * @return boolean detailing whether the file is accessible
 */
void read_battle_print(FILE* in, size_t btl_num, int* btl_valu, gmap *m);

/**
 * Cleans up entire hash map and values
 * @param m a pointer to the hasmap
 * @param battlefield values, frees battlefield values array
 */
void clean_all_gmap(gmap* m, int* battlefield_values);

#endif
