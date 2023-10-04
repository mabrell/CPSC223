#include "pirate_list.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct pirate_list_instance_t
{
    size_t length;
    size_t capacity;
    pirate **pirate_array;
}

pirate_list *list_create()
{
    pirate_list *new_list = malloc(sizeof(pirate_instance_t));
    *new_list->length = 0; 
    *new_list->capacity = INITIAL_CAPACITY;
    *new_list->pirate_array = malloc((*new_list->capacity)*(sizeof(pirate*)));
    return *new_list;
}






void quicksort(pirate_list *pirates, int low, int high)
{
    
    pirate* pivot = *pirates.pirate_array[high]
    pirate* larger = *pirates.pirate_array[0]
    for (int c = low; c <= high-1; c++)
    {
        if !order_check(**pirates.pirate_array[c], **pivot) //CHECK DOUBLE POINTERS
        {
            *larger = *pirates.pirate[c]
        }
        if  order_check(**pirates.pirate_array[c], **pivot) //CHECK DOUBLE POINTERS
        {
            swap(*pirates, *pirates.pirate_array[c], *larger)
        }
    }
    swap(*pirates, *pivot, *larger)
    pivot_index = list_index_of(*pirates, *pivot) //IS THIS NECESSARY
    if !(low == high)
    {
        quicksort(pirate_list *pirates, low, pivot_index - 1)
        quicksort(*pirates, pivot_index + 1, high)
    }
}




/**
* Sort the list of pirates in lexicographical order by name.
*/
void list_sort(pirate_list *pirates)
{
    size_t low = 0
    size_t high = *pirates->length
    quicksort(*pirates, low, high)
    return *pirates
}


bool order_check(char* a, char* b)
{
    int result = strcomp(*a, *b);
    if (result >= 0)
    {
        return false
    }
    if (result < 0)
    {
        return true
    }
    else
        printf("Something went wrong with your order check")
}

void swap(pirate_list* pirate_list_instance,size_t idxa, size_t idxb)
{
    pirate temp = *pirate_list_instance[idxa];
    *pirate_list_instance[idxa] = *pirate_list_instance[idxb]; //Doest this work?? the double * feels funky
    *pirate_list_instance[idxb] = temp;
}




/**
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates)
{
    int pirate_length = *pirate.length; //Is this correct syntax?
    return pirate_length
}


//To be used right before you add another one
void list_expand_if_necessary(pirate_list *pirates)
{
    if (list_length(*pirates) = (*pirates.capacity))
    {
        *pirates.capacity = 2 (*pirates.capacity);
        int new_capacity = *pirates.capacity;
        *pirates.pirate_array = realloc(*pirate_array, sizeof(*pirates.capacity * sizeof(char*)));
        fprintf(stderr, "Expand to %zu\n", new_capacity);
    }
    
        
}


/**
* Only if there is no pirate in the list with the same name as p, insert
*  pirate p into the list at index idx by copying the pointer, shifting the
*  latter part of the list one "slot" to the right.
*
* If there is a pirate in the list with the same name as p, do nothing, and
*  return p (the pirate that was not inserted).
*
* If the pirate was inserted into the list, return NULL.
*
* If p is added to the list, the list claims ownership of the pirate pointed
*  to by p; otherwise ownership remains with p.
*/

//Checks to see whether a pirate of a certain name exists, returns true if so
bool pirate_existence(char* name, pirate_list *pirates)
{
    size_t list_length = *pirates.length;
    size_t pirate_found = false;
    for (int c = 0; c <= list_length; c++) //Is this <= ok?
    {
        if (compareArray(*pirates.pirate_array[c], *p))
        {
            pirate_found = true;
        }
    }
    return pirate_found;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    if (pirate_existence(*p.name))
    {
        length = *pirates.length
        for (int = idx; c <= length; c++) //Might need to idx - 1 or smth here
        {
            index = (length - c);
            held_character = *pirates[index];
            *pirates[index + 1] = held_character;
        }
        *pirates[idx] = p; //Ownership???
        return NULL;
    }
    return p;
}


/**
* Remove the pirate from the list with the same name as p, and return a
*  pointer to it.
* If there is no pirate in the list with the same name as p, return NULL.
*
* The caller of this function is responsible for freeing the returned pirate
*   if it is not NULL.
*/
pirate *list_remove(pirate_list *pirates, pirate *p)
{
    if (!pirate_existence(*p.name))
    {
        return NULL;
    }
    idx = list_index_of(*pirates, *p)
    length = *pirates.length
    removed_pirate_pointer = *pirates[idx]
    for (int = idx; c <= length - 1; c++) //Might need to idx - 1 or smth here
    {
        index = (length - c);
        held_character = *pirates[index + 1];
        *pirates[index] = held_character;
    }
    return removed_pirate_pointer;

}


void list_contract_if_necessary(pirate_list *pirates)
{
    if ((list_length(*pirates) < (*pirates.capacity / 4)))
    {
        *pirates.capacity = (*pirates.capacity) / 2;
        int new_capacity = *pirates.capacity;
        *pirates.pirate_array = realloc(*pirate_array, sizeof(*pirates.capacity * sizeof(char*)));
        fprintf(stderr, "Contract to %zu\n", new_capacity);
    }
}

size_t list_index_of(pirate_list *pirates, pirate *p)
{
    size_t list_length = *pirates.length;
    size_t correct_pirate = (list_length + 36);
    for (int c = 0; c <= list_length; c++) //Is this <= ok?
    {
        if (compareArray(*pirates.pirate_array[c].name, *p.name))
        {
            correct_pirate = c;
        }
    }
    return correct_pirate;
}

pirate *list_access(pirate_list *pirates, size_t idx) //Does this preserve ownership?
{
    pirate *desired_pirate_pointer = *pirates.pirate_array[idx];
    return *desired_pirate_pointer;
}



/**
* Free all memory associated with the list, including the pirates in the list.
*/
void list_destroy(pirate_list *pirates)
{
    destroy_range = *pirate->capacity //Check if its ok to potentially destroy uninitialized memory
    for (int c = 0; c <= destroy_range; c++)
    {
        pirate_destroy(*pirates->pirate_array[c])
    }
    free(*pirates->capacity)
    free(*pirates->length)
    free(*pirates->pirate_array)
    free(pirates)
}



//This function compares two arrays inputed via pointer, returns true if same,
//returns false if different
bool compareArray(char *a, char *b)
{
    so_far_so_good = true
    for (int c = 0; c <= 127; c++) //Is this <= ok?
    {
        if (*a[c] != *b[c])
        {
            so_far_so_good = false
        }
    }
    if so_far_so_good
    {
        return true
    }
    else
    {
        return false
    }
}