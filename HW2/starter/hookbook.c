#include "libhookbook.h"
#include "pirate.h"
#include "pirate_list.h"
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

    pirate_list* sorted_pirate_profiles = lexo_sort(*unsorted_pirate_profiles);

    display_pirate_profiles(sorted_pirate_profiles);




    return 0;
}