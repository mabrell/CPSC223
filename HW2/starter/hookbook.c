#include "libhookbook.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef INITIAL_CAPACITY
#define INITIAL_CAPACITY 25
#endif

int main(int argc, char *argv[])
{
    if (!validity_check_a(argc))
    {
        return 1;
    }
    if (!validity_check_b(argv[1]))
    {
        return 1;
    }


    FILE *file_pointer = fopen(argv[2], "r");
    
    pirate_list* unsorted_pirate_profiles = read_file_and_store(file_pointer);

	list_sort(unsorted_pirate_profiles);

	size_t length = sorted_pirate_profiles->length;
	for (size_t i = 0; i < length; i++)
	{
		pirate_print((sorted_pirate_profiles->pirate_array)[i], stdout);
	}

    return 0;
}