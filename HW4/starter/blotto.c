#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "libblotto.h"
#include "string_key.h"
#include "entry.h"

/**
 * Main File for blotto
 * Author: Mason Abrell
 * Pset 4
 * Date: 11/4/2023
 */

int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		return -1;
	}
	
	int* battlefield_values = malloc((argc-1) * sizeof(int));
	for (size_t i = 0; i < (argc-1); i++)
	{
		battlefield_values[i] = (int) atoi(argv[i+1]);
	}

	gmap* new_bmap = bmap_create();
	int error_result = read_and_store(stdin, new_bmap, argc-1);
	if (error_result == -1)
	{
		clean_all_gmap(new_bmap, battlefield_values);
		return -1;
	}
	read_battle_print(stdin, argc-1, battlefield_values, new_bmap);	
	clean_all_gmap(new_bmap, battlefield_values);
	return 0;
}
