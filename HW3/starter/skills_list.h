#include <stddef.h>
#include <stdio.h>

#ifndef __SKILLS_LIST_H__

#define __SKILLS_LIST_H__


/*
Header file for skills list for Hookbook assignments for CPSC 223 Fall 2023.

Author: Mason Abrell
*/

/**
 * Type of a list of skills, as an opaque struct.
 */
typedef struct skills_list_instance_t skills_list;

//Creates a skill_list
skills_list *skills_list_create();

//Destroys a skills list
void skills_list_destroy(skills_list* target);

//Getter, returns the length of the skill list
size_t skills_list_length(skills_list* skill_scroll);

//Appends a new skill to the list of skills
void skills_list_append(skills_list* skill_scroll, char* skill_name);

//Removes the first node in the linked list, does nothing if length = 0
void skills_list_remove(skills_list* skills_scroll);

char* get_first_name(skills_list* skills_scroll);

//Prints skills according to README specifications
void skills_list_print(skills_list* skills_scroll, FILE *restrict output);


#endif