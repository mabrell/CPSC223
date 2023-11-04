#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "gmap.h"
#include "string_key.h"
#include "libblotto.h"

/**
 * Implementation File for blotto functions
 * Author: Mason Abrell
 * Pset 4
 * Date: 11/4/2023
 */

//runs a battle
void run_btl(char* p_a, char* p_b, size_t btl_num, int* btl_valu, gmap *m)
{
	float p_a_pt = 0; //Sets initial point totals for the two plyrs
	float p_b_pt = 0;
	int* plyr_a_dist = gmap_get(m, p_a);
	int* plyr_b_dist = gmap_get(m, p_b);
	for (size_t i = 0; i < btl_num; i++)
	{
		float current_pt_value = btl_valu[i];
		if (plyr_a_dist[i] > plyr_b_dist[i])
		{
			p_a_pt += current_pt_value;
		}
		if (plyr_a_dist[i] < plyr_b_dist[i])
		{
			p_b_pt += current_pt_value;
		}
		if (plyr_a_dist[i] == plyr_b_dist[i])
		{
			current_pt_value = current_pt_value/2;
			p_a_pt += current_pt_value;
			p_b_pt += current_pt_value;
		}
	}
	if (p_a_pt < p_b_pt) //check if should switch order
	{
		fprintf(stdout, "%s %.1f - %s %.1f\n", p_b, p_b_pt, p_a, p_a_pt);
	}
	else
	{
		fprintf(stdout, "%s %.1f - %s %.1f\n", p_a, p_a_pt, p_b, p_b_pt);
	}
	
	
}

/**
 * Creates an empty blotto map that uses the functions corresponding to strings
 *
 * @return a pointer to the new map or NULL if it could not be created;
 * it is the caller's responsibility to destroy the map
 */
gmap* bmap_create()
{
	return gmap_create(duplicate, compare_keys, hash29, free);	
}


//Implementation for new read I
int read_and_store(FILE *in, gmap* m, size_t battlefields)
{
	int read_state = -1; //read state defins how the function should proceed
						//-1-> continue as normal, -2->reached end, -3, error
	bool first_time = true;
	int pt = 15; //Arbitrary starting number
	while (read_state != -2)
	{
		read_state = read_profile(in, m, battlefields, first_time, pt);
		if (read_state > 0) //Readstate is only above zero on first successful
							//run, when pt is set, which checks for uneven pt
							//allotment
		{
			pt = read_state;
			first_time = false;
		}
		if (read_state == -3)
		{
			return -1; //error detected, return nothing from program overall
		}
		
	}
	//if it reaches this point, it has finished reading the initial players dist
	return 0;
}

//Reads a single profile and returns a integer that specifies read state
int read_profile(FILE *in, gmap* m, size_t battlefields, bool ft, int pt)
{
	size_t char_count = 0;
	char* player_id = malloc(32 * sizeof(char));
	bool comma_found = false;
	while (comma_found == false)
	{
		char_count++;
		if (char_count == 32)
		{
			free(player_id); //In this case, the name is too long, so we ignore
			return -3;
		}
		
		char result = fgetc(in);
		if (result == '\n') //We've hit the end of the profiles section
		{
			free(player_id);
			return -2;
		}
		
		if (result == EOF)
		{
			free(player_id);
			return -3;
		}
		if (result == ',')
		{
			comma_found = true;
			continue;
		}
		player_id[char_count-1] = (char) result;
	}
	player_id[char_count - 1] = '\0';
	int* value_array = malloc(battlefields * sizeof(int));
	int pt_sum = 0;
		//At this point the player id should be read

	for (size_t i = 0; i < battlefields; i++)
	{
		int str[1];
		int valu_result = fscanf(in, "%d[^,\n]", str);
		value_array[i] = str[0];
		pt_sum += str[0];
	
		
		if (valu_result != 1)
		{
			free(player_id);
			free(value_array);
			return -3;
		}
		
		char check_result = fgetc(in);
		if (check_result == ',')
		{
			continue;
		}
		if ((i == battlefields - 1) && (check_result == '\n'))
		{
			if ((ft == false) && (pt_sum != pt))
			{
				free(player_id);
				free(value_array);
				return -3;
			}
			gmap_put(m, player_id, value_array);
			free(player_id);
			if (ft == true)
			{
				return pt_sum;
			}
			
			return -1;
		}
	}
	//This means we have to chop off the rest of the line and move on to next
	free(player_id);
	free(value_array);
	return -3;
}

//reads pairs, calculates, and prints blotto matches
void read_battle_print(FILE* in, size_t btl_num, int* btl_valu, gmap *m)
{
	bool end_of_file_found = false;
	char* p_one = malloc(32 * sizeof(char)); //Allocating memory for the two ids
	char* p_two = malloc(32 * sizeof(char));
	while (end_of_file_found == false)
	{
		int result = fscanf(in, "%s[^\n]", p_one); //If 31+ characters,cut
		char char_result = fgetc(in);
		if (char_result == ' ')
		{
			int result_two = fscanf(in, "%s[^\n]", p_two);
			if (gmap_contains_key(m, p_one) && gmap_contains_key(m,p_two))
			{
				run_btl(p_one, p_two, btl_num, btl_valu, m);
				bool devour_new_line = false; //This keeps track if we've eaten
											//the new line
				while (devour_new_line == false)
				{
					int devour_result = fgetc(in);
					if (devour_result == '\n')
					{
						devour_new_line = true;
					}
					if (devour_result == EOF)
					{
						devour_new_line = true;
						end_of_file_found = true;
					}
					
				}
			}
			if (char_result == EOF)
			{
				end_of_file_found = true;
			}
			if (result_two == EOF)
			{
				end_of_file_found = true;
			}
		}
		if (result == EOF)
		{
			end_of_file_found = true;
		}
	}
	free(p_one);
	free(p_two);
	return;
}

//Function that cleans up entire gmap and other values
void clean_all_gmap(gmap* m, int* battlefield_values)
{
	size_t size = gmap_size(m);
	char** key_array = (char**) gmap_keys(m);
	for (size_t i = 0; i < size; i++)
	{
		free(gmap_remove(m, key_array[i]));
	}
	gmap_destroy(m);
	free(key_array);
	free(battlefield_values);
}