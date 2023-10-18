#include "skills_list.h"
#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

int name_comp(const void* argh1, const void* argh2)
{
	pirate* first_pirate = (pirate*)argh1;
	pirate* second_pirate = (pirate*)argh2;
	const char* first_name = pirate_name(first_pirate);
	const char* second_name = pirate_name(second_pirate);
	int result_value = strcmp(first_name, second_name);
	return result_value;
}



int vessel_comp(const void* argh1, const void* argh2)
{
	pirate* first_pirate = (pirate*)argh1;
	pirate* second_pirate = (pirate*)argh2;
	const char* first_vessel = pirate_vessel(first_pirate);
	const char* second_vessel = pirate_vessel(second_pirate);
	return strcmp(first_vessel, second_vessel);
}

int treasure_comp(const void* argh1, const void* argh2)
{
	pirate* first_pirate = (pirate*)argh1;
	pirate* second_pirate = (pirate*)argh2;
	const size_t first_treasure = pirate_treasure(first_pirate);
	const size_t second_treasure = pirate_treasure(second_pirate);
	if (first_treasure > second_treasure)
	{
		return -1;
	}
	if (first_treasure == second_treasure)
	{
		return 0;
	}
	if (first_treasure < second_treasure)
	{
		return 1;
	}
	else
	{
		return 0; //THIS SHOULD NEVER BE REACHED
	}
}

int main(int argc, char *argv[])
{
	bool valid_argc = argc_validity_check(argc);
	if (!valid_argc)
	{
		return 1;
	}
	if (argc == 3)
	{
		bool valid = argc3_validity_check(argv[1], argv[2]);
		if (!valid)
		{
			return 1;
		}
	}
	if (argc == 4)
	{
		bool valid = argc4_validity_check(argv[1], argv[2], argv[3]);
		if (!valid)
		{
			return 1;
		}
	}
	FILE *fptr;
	FILE *fptr_two;
	//char flag;
	pirate_list* new_pirate_list; //Is this necessary/ will it break?
	if (argc == 3)
	{
		//list_destroy(new_pirate_list);
		new_pirate_list = list_create(name_comp); //This is very sketchy
		set_sort_type(new_pirate_list, 'n');
		fptr = fopen((const char *) argv[1], "r");
		fptr_two = fopen((const char *) argv[2], "r");
	}
	if (argc == 4)
	{
		//list_destroy(new_pirate_list);
		new_pirate_list = argc4_prcs_pirate(argv[1], argv[2], argv[3], name_comp, treasure_comp, vessel_comp);
		fptr = argc4_prcs_pirate_file(argv[1], argv[2], argv[3]);
		fptr_two = argc4_prcs_captn_file(argv[1], argv[2], argv[3]);
		//flag = argc4_prcs_flag(argv[1], argv[2], argv[3]);
		//set_sort_type(new_pirate_list, flag);
	}
	bool EOF_reached = false;
	while (!EOF_reached)
	{
		pirate* new_pirate_pointer = pirate_read(fptr);
		if (new_pirate_pointer == NULL)
		{
			EOF_reached = true;
		}
		else
		{
			pirate* p = list_insert(new_pirate_list, new_pirate_pointer, 0);
			if (p != NULL)
			{
				pirate_destroy(p);
			}
			
		}
	}
	list_sort(new_pirate_list);
	captain_read(new_pirate_list, fptr_two);
	
	size_t length = list_length(new_pirate_list);
	for (size_t i = 0; i < length; i++)
	{
		pirate_print(list_access(new_pirate_list, i), stdout);
	}
	fclose(fptr);
	fclose(fptr_two);

	list_destroy(new_pirate_list);
	return 0;
}







// For pirate_read testing:
// 	int access_marker = access("test_file_one.txt", F_OK);
// 	access_marker = access_marker + access("test_file_one.txt", R_OK);
//     if (access_marker != 0) //Ensures file is accessible and readable
//     {
// 		printf("yikes, no access");
//         return -1;
//     }
// 	FILE *fptr = fopen((const char *) "test_file_one.txt", "r");
// 	pirate* new_pirate_pointer = pirate_read(fptr);
// 	printf("print vessel: %i \n", pirate_treasure(new_pirate_pointer));
// 	pirate_print(new_pirate_pointer, stdout);
// 	pirate_destroy(new_pirate_pointer);
// 	fclose(fptr);



//For pirate.c testing:
	// pirate* new_pirate = pirate_create();
	// char* temp_name = "billy";
	// pirate_set_name(new_pirate, temp_name);
	// char* temp_rank = "admiral";
	// pirate_set_rank(new_pirate, temp_rank);
	// char* temp_vessel = "Millenium Falcon";
	// pirate_set_vessel(new_pirate, temp_vessel);
	// char* temp_port = "Lisbon";
	// pirate_set_port(new_pirate, temp_port);
	// unsigned int temp_treasure = 9999;
	// pirate_set_treasure(new_pirate, temp_treasure);
	// pirate_print(new_pirate, stdout);
	// pirate_destroy(new_pirate);



// For skills testing

// 	skills_list* new_skills_list = skills_list_create();
// 	char* skill_one = "b";
// 	char* skill_two = "a";
// 	char* skill_three = "b";
// 	char* skill_four = "a";
// 	char* skill_five = "c";
// 	skills_list_append(new_skills_list, skill_one);
// 	skills_list_print(new_skills_list, stdout);
// 	printf("length of skills_list, post 1: %lu \n", skills_list_length(new_skills_list));
// 	skills_list_append(new_skills_list, skill_two);
// 	skills_list_print(new_skills_list, stdout);
// 	printf("length of skills_list, post 2: %lu \n", skills_list_length(new_skills_list));
// 	skills_list_append(new_skills_list, skill_three);
// 	skills_list_print(new_skills_list, stdout);
// 	printf("length of skills_list, post 3: %lu \n", skills_list_length(new_skills_list));
// 	skills_list_append(new_skills_list, skill_four);
// 	skills_list_print(new_skills_list, stdout);
// 	printf("length of skills_list, post 4: %lu \n", skills_list_length(new_skills_list));
// 	skills_list_append(new_skills_list, skill_five);
// 	skills_list_print(new_skills_list, stdout);
// 	printf("length of skills_list, post 5: %lu \n", skills_list_length(new_skills_list));
// 	skills_list_print(new_skills_list, stdout);
// 	skills_list_destroy(new_skills_list);