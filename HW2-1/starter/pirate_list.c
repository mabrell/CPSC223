#include "pirate_list.h"
#include "pirate.h"
#include <stdbool.h>
#include <string.h>


#ifndef INITIAL_CAPACITY
#define INITIAL_CAPACITY 25
#endif

#ifndef RESIZE_FACTOR
#define RESIZE_FACTOR 2
#endif

struct pirate_list_instance_t
{
    size_t length;
    size_t capacity;
    pirate **pirate_array;
};


/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 * Also, i made this funciton give initial values to the list
 */
pirate_list *list_create()
{
	pirate_list *new_list = malloc(sizeof(pirate_list));
	new_list->length = 0;
	new_list->capacity = INITIAL_CAPACITY;
	new_list->pirate_array = malloc((new_list->capacity) * pirate_size());
	return new_list;
}

//Uses quicksort to sort pirates' pirate_array lexicographically
void list_sort(pirate_list *pirates)
{
	size_t low = 0;
	if (list_length(pirates) == 0)
	{
		return;
	}
	
	size_t high = list_length(pirates) - 1;
	quicksort(pirates, low, high);
}

//This quicksort sorts pirates' pirate_array lexicographically using recursion
void quicksort(pirate_list *pirates, int low, int high)
{
	if (low == high)
	{
		return;
	}
	
	if (low + 1 == high) //This checks for a 2 cell array, which sorts different
	{
		if (pirate_compare(pirates->pirate_array[low], pirates->pirate_array[high]) > 0)
		{
			swap(pirates, low, high);
		}
		return;
	}
	
	bool pointers_are_equal = false;
	size_t pivot = high;
	size_t left = low;
	size_t right = high-1;
	size_t pivot_target;
	while (pointers_are_equal == false)
	{
		while (pirate_compare(pirates->pirate_array[left], pirates->pirate_array[pivot]) < 0)
		{
			left++;
		}
		while ((pirate_compare(pirates->pirate_array[right], pirates->pirate_array[pivot]) >= 0) && (pointers_are_equal == false))
		{
			if (left >= right)
			{
				pointers_are_equal = true;
				pivot_target = left;
			}
			else
			{
				right--;
			}
		}
		if (left >= right)
		{
			pointers_are_equal = true;
			pivot_target = left;
		}
		if (pointers_are_equal == false)
		{
			swap(pirates, left, right);
		}
	}
	swap(pirates, pivot_target, pivot);
	
	// if (low + 2 == high)
	// {
	// 	return; //In this case, the subarray is 3 long, so it is perfectly sorted
	// }

	quicksort(pirates, low, pivot_target-1);
	quicksort(pirates, pivot_target, high);
	return;
}



//Swaps the array location of two pirate pointers
void swap(pirate_list* pirate_list_instance,size_t idxa, size_t idxb)
{
    pirate* temp = pirate_list_instance->pirate_array[idxa];
    pirate_list_instance->pirate_array[idxa] = pirate_list_instance->pirate_array[idxb]; //Doest this work?? the double * feels funky
    pirate_list_instance->pirate_array[idxb] = temp;
}


//To be used right before you add a pirate, expands list if necessary
void list_expand_if_necessary(pirate_list *pirates)
{
    if (list_length(pirates) == (pirates->capacity))
    {
        pirates->capacity = RESIZE_FACTOR * (pirates->capacity);
        size_t new_capacity = pirates->capacity;
        pirates->pirate_array = realloc(pirates->pirate_array, pirates->capacity * get_pirate_size());
        fprintf(stderr, "Expand to %zu\n", new_capacity);
    }
}

//To be used right before you add a pirate, contracts list if necessary
void list_contract_if_necessary(pirate_list *pirates)
{
    if ((list_length(pirates) < (pirates->capacity / 4)))
    {
        pirates->capacity = (pirates->capacity) / RESIZE_FACTOR;
        size_t new_capacity = pirates->capacity;
        pirates->pirate_array = realloc((*pirates).pirate_array, pirates->capacity * sizeof(char*));
        fprintf(stderr, "Contract to %zu\n", new_capacity);
    }
}

//Getter for pirate_list capacity
size_t get_capacity_value(pirate_list* pirates)
{
	return pirates->capacity;
}

/**
 * Return the index of the pirate with the same name as p, or a value greater
 *  than or equal to the length of the list if the pirate is not in the list.
 *
 * Ownership of p is not changed.
 */
size_t list_index_of(pirate_list *pirates, pirate *p)
{
	size_t list_length = pirates->length;
    size_t correct_pirate = (list_length + 36);
    for (int c = 0; c < list_length; c++) //Is this <= ok?
    {
        if (strcmp(pirate_name(list_access(pirates, c)), pirate_name(p)) == 0)
        {
            correct_pirate = c;
        }
    }
    return correct_pirate;
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
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
	if (!pirate_existence(pirates, pirate_name(p)))
    {
		list_expand_if_necessary(pirates);
        size_t length = pirates->length;
        for (int c = 1; c <= length-idx; c++) //Loop starts pointing at the one that needs to be moved right
        {
            size_t index = (length - c);
            pirate* held_character = pirates->pirate_array[index];
            pirates->pirate_array[index + 1] = held_character;
        }
        pirates->pirate_array[idx] = p;
		pirates->length++;
        return NULL;
    }
    return p;
}


bool pirate_existence(pirate_list *pirates,const char* name)
{
	size_t length = list_length(pirates);
    bool pirate_is_stored = false;
    for (int c = 0; c < length; c++)
    {
        if (strcmp(pirate_name(list_access(pirates, c)), name) == 0)
        {
            pirate_is_stored = true;
        }
    }
    return pirate_is_stored;
}





/**
 * Remove the pirate from the list with the same name as p, and return a
 *  pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL.
 *
 * The caller of this function becomes the owner of the returned pirate if it
 *  is not NULL.
 */
pirate *list_remove(pirate_list *pirates, pirate *p)
{
	if (!pirate_existence(pirates, pirate_name(p)))
    {
        return NULL;
    }
	list_contract_if_necessary(pirates);
    size_t idx = list_index_of(pirates, p);
    size_t length = list_length(pirates);
    pirate* removed_pirate_pointer = pirates->pirate_array[idx];
    for (int c = idx; c < length; c++) //Might need to idx - 1 or smth here
    {
        pirate* held_character = pirates->pirate_array[c+1];
        pirates->pirate_array[c] = held_character;
    }
	pirates->length--;
    return removed_pirate_pointer;

}

/**
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL
 *  if idx is not a valid index (i.e., it is >= the length of the list).
 *
 * Ownership of the pirate remains with the list.
 */
pirate *list_access(pirate_list *pirates, size_t idx)
{
	pirate *desired_pirate_pointer;
	if (((idx) >= (pirates->length)) || (idx < 0))
	{
		desired_pirate_pointer = NULL;
	}
	else
	{
		desired_pirate_pointer = pirates->pirate_array[idx];
	}
    return desired_pirate_pointer;
}

// /**
//  * Sort the list of pirates in lexicographical order by name.
//  */
// void list_sort(pirate_list *pirates)
// {
// 	quicksort(pirates, 0 , list_length(pirates));
// }

/**
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates)
{
	return pirates->length;
}

/**
 * Free all memory associated with the list, including the pirates in the list.
 */
void list_destroy(pirate_list *pirates)
{
	size_t length = list_length(pirates);
	if (length > 0)
	{
		for (size_t i = 0; i < length; i++)
		{
			pirate_destroy(pirates->pirate_array[i]);
		}
	}
	free(pirates->pirate_array);
	free(pirates);
}
