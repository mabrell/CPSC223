#include "pirate.h"
#include "skills_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct suspicious_pirate { //I named it suspicious pirate bc they're hiding
                            //behind an opaque construct!
    char* name;
    char* rank_name;
    char* vessel_name;
    char* port_name;
    size_t treasure_amount;
	bool rank_changed;
	bool treasure_changed;
	bool vessel_changed;
	bool port_changed;
	bool captain_changed;

	const pirate* captain_pointer;
    skills_list* skills;
};



//This function creates a pirate, allocating memory for the struct itself
pirate* pirate_create(void)
{
	pirate *new_p = malloc(sizeof(pirate));
	new_p->skills = skills_list_create();
	new_p->treasure_changed = false;
	new_p->vessel_changed = false;
	new_p->port_changed = false;
	new_p->rank_changed = false;
	new_p-> captain_changed = false;
	return new_p;
}


//sets captain changed
void set_captain_changed(pirate* p, bool value)
{
	p->captain_changed = value;
}

//gets captain changed
bool get_captain_changed(pirate* p)
{
	return p->captain_changed;
}

//returns the sizeof pirate
size_t get_pirate_size()
{
	return sizeof(pirate);
}




//This is simply a getter that returns the sizeof() of a pirate struct
size_t pirate_size()
{
	return sizeof(pirate);
}



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
pirate *pirate_read(FILE *restrict input)
{
	pirate* new_pirate_pointer = pirate_create();
	bool found_a_pirate = false;
	char* handover_p = malloc(128 * sizeof(char));
	char* temp_pointer = handover_p;
	while (!found_a_pirate)
	{
		bool newline = false;
	
 		handover_p = fgets(handover_p, 128, input);
		if (handover_p == NULL)//This should stop it at the end 
		{
			free(handover_p);
			free(temp_pointer);
			skills_list_destroy(new_pirate_pointer->skills);
			free(new_pirate_pointer);
			found_a_pirate = false;
			return NULL;
		}
		if (handover_p[0] == '\n')
		{
			//free(handover_p);
			newline = true;
		}
		if (newline == false)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0'; //DOES THIS BREAK SHIT
			pirate_set_name(new_pirate_pointer, handover_p);
			found_a_pirate = true;
			free(handover_p);
		}
	}
	bool found_end_of_profile = false;
	char* vessel_substring = "vessel:";
	char* rank_substring = "rank:";
	char* treasure_substring = "treasure:";
	char* skill_substring = "skill:";
	char* port_substring = "port:";
	while (!found_end_of_profile)
	{
		char* handover_p = malloc(128 * sizeof(char));
		char* temp_pointer = handover_p;
		handover_p = fgets(handover_p, 128, input);
		if (handover_p == NULL)//This should stop it at the end 
		{

			free(handover_p);
			free(temp_pointer);
			found_end_of_profile = true;
		}
		else if (strstr(handover_p, vessel_substring) != NULL)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0';
			pirate_set_vessel(new_pirate_pointer, pcc(handover_p));
			free(handover_p);
		}
		else if (strstr(handover_p, rank_substring) != NULL)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0';
			pirate_set_rank(new_pirate_pointer, pcc(handover_p));
			free(handover_p);
		}
		else if (strstr(handover_p, port_substring) != NULL)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0';
			pirate_set_port(new_pirate_pointer,pcc(handover_p));
			free(handover_p);
		}
		else if (strstr(handover_p, skill_substring) != NULL)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0';
			char* t = handover_p; //I used t here in order to fit style
			skills_list_append(new_pirate_pointer->skills, pcc(t));
			free(handover_p);
		}
		else if (strstr(handover_p, treasure_substring) != NULL)
		{
			size_t prev_char_count = strcspn(handover_p, "\n");
			handover_p[prev_char_count] = '\0';
			int treasure_handover_one = atoi(pcc(handover_p));
			unsigned int treasure_handover_two = treasure_handover_one;
			pirate_set_treasure(new_pirate_pointer, treasure_handover_two);
			free(handover_p);
		}
		else if (handover_p[0] == '\n')
		{
			free(handover_p);
			found_end_of_profile = true;
		}
	}
	
	return new_pirate_pointer;
}

char* pcc(char* input)
{
	bool found_colon = false;
	size_t index_counter = 0;
	size_t value_start_index = 0;
	while (!found_colon)
	{
		if (input[index_counter] == ':')
		{
			found_colon = true;
			value_start_index = index_counter + 1;
		}
		index_counter++;
	}
	char* output = input + value_start_index;
	return output;
}

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 */
void pirate_print(const pirate *p, FILE *restrict output) //NEEDS WORK
{
	char* name = p->name;
	fprintf(output, "%s \n", name);

	if ((p->captain_changed))
	{
		char* captain_name = p->captain_pointer->name;
		fprintf(output, "    Captain: %s \n", captain_name);
	}
	if ((p->rank_changed))
	{
		char* rank_name = p->rank_name;
		fprintf(output, "    Rank: %s \n", rank_name);
	}

	if ((p->vessel_changed))
	{
		char* vessel_name = p->vessel_name;
		fprintf(output, "    Vessel: %s \n", vessel_name);
	}

	if ((p->port_changed))
	{
		char* port_name = p->port_name;
		fprintf(output, "    Port: %s \n", port_name);
	}

	if ((p->treasure_changed))
	{
		unsigned int treasure_amount = p->treasure_amount;
		fprintf(output, "    Treasure: %u \n", treasure_amount);
	}

	if ((p->skills) != NULL)
	{
		skills_list_print(p->skills, output);
	}

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
 * Returns the vessel of the pirate.
 */
const char *pirate_vessel(const pirate *p)
{
	return p->vessel_name;
}

/**
 * Sets the vessel of a pirate.
*/
void pirate_set_vessel(pirate *p, const char* vessel)
{
	p->vessel_name = malloc(128 * sizeof(char));
	p->vessel_changed = true;
	strcpy(p->vessel_name, vessel);
}

/**
 * Returns the favorite port of call of the pirate.
 */
const char *pirate_port(const pirate *p)
{
	return p->port_name;
}

/**
 * Sets the favorite port of call of a pirate.
*/
void pirate_set_port(pirate *p, const char* port)
{
	p->port_name = malloc(128 * sizeof(char));
	p->port_changed = true;
	strcpy(p->port_name, port);
}

/**
 * Returns the rank of the pirate.
 */
const char *pirate_rank(const pirate *p)
{
	return p->rank_name;
}

/**
 * Sets the rank of a pirate.
*/
void pirate_set_rank(pirate *p, const char* rank)
{
	p->rank_name = malloc(128 * sizeof(char));
	p->rank_changed = true;
	strcpy(p->rank_name, rank);
}

/**
 * Returns the treasure of the pirate.
 */
unsigned int pirate_treasure(const pirate *p)
{
	return p->treasure_amount;
}



/**
 * Sets the treasure of a pirate.
*/
void pirate_set_treasure(pirate *p, unsigned int treasure)
{
	p->treasure_amount = treasure;
	p->treasure_changed = true;
}


/**
 * Returns a pointer to the profile of the pirate's captain.
 */
const pirate *pirate_captain(const pirate *p)
{
	return p->captain_pointer;
}

/**
 * Sets the captain of a pirate.
 */
void pirate_set_captain(pirate * p, const pirate *cpt)
{
	p->captain_pointer = cpt;
	p->captain_changed = true;
}

/**
 * Returns a pointer to the list of skills of the pirate.
 */
skills_list *pirate_skills(const pirate *p)
{
	return p->skills;
}

/**
 * Frees all memory associated with this pirate. This function claims ownership
 *  of p.
 */
void pirate_destroy(pirate *p)
{
	free(p->name);
	if ((p->vessel_changed))
	{
		free(p->vessel_name);
	}
	if ((p->port_changed))
	{
		free(p->port_name);
	}
	if ((p->rank_changed))
	{
		free(p->rank_name);
	}
	skills_list_destroy(p->skills);

	if (!(get_captain_changed(p))) //DOUBLE CHECK THIS LATER
	{
		p->captain_pointer = NULL;
	}
	free(p);
}

bool get_treasure_change(pirate* jack)
{
	return jack->treasure_changed;
}

bool get_vessel_change(pirate* jack)
{
	return jack->vessel_changed;
}

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 */
int pirate_compare(pirate *a, pirate *b)
{
	return strcmp(a->name, b->name);
}