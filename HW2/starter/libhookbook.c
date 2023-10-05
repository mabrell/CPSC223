#include "libhookbook.h"
#include "pirate.h"
#include "pirate_list.h"
#include <stdio.h>
#include <stdbool.h>

//Checks for the right number of arguements, true if correct, false if not
bool validity_check_a( int argc)
{
    if (argc != 2) //Ensures user inputs 2 arguements
    {
        return false;
    }
    else
        return true;
}


//CHecks for an accessible file, true if correct, false if not
bool validity_check_b(char* file_name)
{
    int access_marker = access(file_name);
    if (access_marker != 0) //Ensures file is accessible and readable
    {
        return false;
    }
    else
        return true;
}






//Read and store all values for the input file, returning the pointer to a list
pirate_list* read_file_and_store(FILE *file_pointer)
{
    pirate_list* pirate_list_pointer = list_create();
    bool reached_end = false;
    size_t counter = 0;
    while (!reached_end)
    {
        pirate_list_pointer->pirate_array[counter] = pirate_read(file_pointer); //Should there be a * in front of the function?
        if (pirate_list_pointer->pirate_array[counter] = NULL) //This essentially means that if its an invalid result, it'll just move on, and overwrite that cell with the next pirate
        {
            if (feof(file_pointer) != 0) //triggering this if statement means you've reached the end of the file
            {
                reached_end = true;
            }
        
        }
        if (pirate_existence(pirate_list_pointer->pirate_array[counter], *pirate_list_pointer))
        {
            pirate_destroy(pirate_list_pointer->pirate_array[counter]);
        }
        else if (pirate_list_pointer->pirate_array[counter] != (NULL))
        {
			list_expand_if_necessary(pirate_list_pointer);
			list_contract_if_necessary(pirate_list_pointer);
            counter++;//Use return of fgets to decide what to do, if return null or newline, use destroy pirate
        }
    }
    return pirate_list_pointer;
}