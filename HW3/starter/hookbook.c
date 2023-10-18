#include "skills_list.h"
#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

int n_comp(const void* argh1, const void* argh2)
{
	pirate* first_pirate = (pirate*)argh1;
	pirate* second_pirate = (pirate*)argh2;
	const char* first_name = pirate_name(first_pirate);
	const char* second_name = pirate_name(second_pirate);
	int result_value = strcmp(first_name, second_name);
	return result_value;
}



int v_comp(const void* argh1, const void* argh2)
{
	pirate* first_pirate = (pirate*)argh1;
	pirate* second_pirate = (pirate*)argh2;
	const char* first_vessel = pirate_vessel(first_pirate);
	const char* second_vessel = pirate_vessel(second_pirate);
	return strcmp(first_vessel, second_vessel);
}

int t_comp(const void* argh1, const void* argh2)
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

//Above are all function pointer definitions for later use in the main function

int main(int argc, char *argv[])
{
	if (total_validity_check(argc, argv[1], argv[2], argv[3]) == 1)
	{
		return 1;
	}
	FILE *fptr;
	FILE *fptr_two;
	pirate_list* new_plist;
	if (argc == 3)
	{
		new_plist = list_create(n_comp);
		set_sort_type(new_plist, 'n');
		fptr = fopen((const char *) argv[1], "r");
		fptr_two = fopen((const char *) argv[2], "r");
	}
	if (argc == 4)
	{
		new_plist = argc4_p(argv[1], argv[2], argv[3], n_comp, t_comp, v_comp);
		fptr = argc4_prcs_pirate_file(argv[1], argv[2], argv[3]);
		fptr_two = argc4_prcs_captn_file(argv[1], argv[2], argv[3]);
	}

	pirate_read_and_sort(fptr, fptr_two, new_plist);

	print_whole_list(new_plist);
	clean_up(fptr, fptr_two, new_plist);
	return 0;
}