
#include <stdio.h>
#include <stdbool.h>

#ifndef INITIAL_CAPACITY
#define INITIAL_CAPACITY 25
#endif

int main(int argc, char *argv[])
{
    bool validity_value = validity_check_a(argc)
    if (validity_value = true)
    {
        return 1;
    }
    validity_value = validity_check_b(argv[1])
    {
        return 1;
    }

    char* file_name = malloc(sizeof(argv[2])) //Is this allocation necessary?
    *file_name = argv[2]

    FILE *file_pointer = fopen(*file_name, "r")
    
    pirate_list* unsorted_pirate_profiles = read_file_and_store()

    pirate_list* sorted_pirate_profiles = lexo_sort(*unsorted_pirate_profiles)

    display_pirate_profiles(*sorted_pirate_profiles)




    return 0;
}