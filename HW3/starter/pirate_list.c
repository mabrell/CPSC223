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
	int (*compare_fn)(const void* a, const void* b);
	char sort_type;
};



/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 * Also, i made this funciton give initial values to the list
 */
pirate_list *list_create(int (*comp)(const void *, const void *))
{
	pirate_list *new_list = malloc(sizeof(pirate_list));
	new_list->length = 0;
	new_list->capacity = INITIAL_CAPACITY;
	new_list->pirate_array = malloc((new_list->capacity) * get_pirate_size());
	new_list->compare_fn = comp;
	return new_list;
}

//void arguement_handle(pirate_list* pirates, argv1, arv2)

//Uses quicksort to sort pirates' pirate_array lexicographically
void list_sort(pirate_list *pirates)
{
	size_t low = 0;
	size_t high = list_length(pirates) - 1;
	if (list_length(pirates) == 0)
	{
		return;
	}
	if (get_sort_type(pirates) == 'n')
	{
		quicksort(pirates, low, high);
	}
	else if (get_sort_type(pirates) == 'v')
	{
		high = no_vessel_to_end(pirates);
		quicksort(pirates, low, high);
	}
	else if (get_sort_type(pirates) == 't')
	{
		high = no_treasure_to_end(pirates);
		quicksort(pirates, low, high);
	}
	else
	{
		return;
	}
}

//getter for sort_type
char get_sort_type(pirate_list* pirates)
{
	return pirates->sort_type;
}

//setter for sort_type
void set_sort_type(pirate_list* pirates, char input)
{
	pirates->sort_type = input;
}



//This quicksort sorts pirates' pirate_array lexicographically using recursion
void quicksort(pirate_list *pirates, int low, int high)
{
	if (low == high) //TChecks for a 1 cell array, which doesn't need sorting
	{
		return;
	}
	
	if (low + 1 == high) //This checks for a 2 cell array, which sorts different
	{
		if (pirates->compare_fn(pirates->pirate_array[low], pirates->pirate_array[high]) > 0)
		{
			swap(pirates, low, high);
		}
		return;
	}
	
	bool ptr_equal = false;
	size_t pivot = high;
	size_t left = low;
	size_t right = high-1;
	size_t pivot_target;
	while (ptr_equal == false)
	{
		while (pirates->compare_fn(pirates->pirate_array[left], pirates->pirate_array[pivot]) < 0)
		{
			left++;
		}
		while ((pirates->compare_fn(pirates->pirate_array[right], pirates->pirate_array[pivot]) >= 0) && (ptr_equal == false))
		{
			if (left >= right)
			{
				ptr_equal = true;
				pivot_target = left;
			}
			else
			{
				right--;
			}
		}
		if (left >= right)
		{
			ptr_equal = true;
			pivot_target = left;
		}
		if (ptr_equal == false)
		{
			swap(pirates, left, right);
		}
	}
	swap(pirates, pivot_target, pivot);
	if (pivot_target == low)
	{
		quicksort(pirates, low, low); //Recursive quicksort call
		quicksort(pirates, low + 1, high);
	}
	else if ((pivot_target == high))
	{
		quicksort(pirates, low, high - 1); //Recursive quicksort call
		quicksort(pirates, high, high);
	}
	else
	{
		quicksort(pirates, low, pivot_target-1); //Recursive quicksort call
		quicksort(pirates, pivot_target, high);
	}
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


//Checks to see whether there is already a file in the given pirate_list with
//the inputted name. Returns True if yes, and False if no.
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

//quicksort, but exclusively lexiicographically by name
void quicksort_basic(pirate_list *pirates, int low, int high)
{
	if (low == high) //TChecks for a 1 cell array, which doesn't need sorting
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
	
	bool ptr_equal = false;
	size_t pivot = high;
	size_t left = low;
	size_t right = high-1;
	size_t pivot_target;
	while (ptr_equal == false)
	{
		while (pirate_compare(pirates->pirate_array[left], pirates->pirate_array[pivot]) < 0)
		{
			left++;
		}
		while ((pirate_compare(pirates->pirate_array[right], pirates->pirate_array[pivot]) >= 0) && (ptr_equal == false))
		{
			if (left >= right)
			{
				ptr_equal = true;
				pivot_target = left;
			}
			else
			{
				right--;
			}
		}
		if (left >= right)
		{
			ptr_equal = true;
			pivot_target = left;
		}
		if (ptr_equal == false)
		{
			swap(pirates, left, right);
		}
	}
	swap(pirates, pivot_target, pivot);
	if (pivot_target == low)
	{
		quicksort_basic(pirates, low, low); //Recursive quicksort call
		quicksort(pirates, low + 1, high);
	}
	else if ((pivot_target == high))
	{
		quicksort(pirates, low, high - 1); //Recursive quicksort call
		quicksort(pirates, high, high);
	}
	else
	{
		quicksort(pirates, low, pivot_target-1); //Recursive quicksort call
		quicksort(pirates, pivot_target, high);
	}
	return;
}

//This function moves treasure-less pirates to the end, sorts them
//lexicographically by name, and returns the index before the treasureless
//pirates
size_t no_treasure_to_end(pirate_list* pirates)
{
	size_t length = list_length(pirates);
	size_t treasureless_count = 0;
	size_t index_count = 0;
	if (length == 1)
	{
		return 0;
	}
	
	for (size_t i = 0; i < length; i++)
	{

		pirate* current_pirate = pirates->pirate_array[index_count];
		bool current_p_treasure_change = get_treasure_change(current_pirate);
		if (!current_p_treasure_change)
		{
			treasureless_count++;
			pirate* handover_pirate = pirates->pirate_array[index_count];
			for (size_t t = index_count; t < length-1; t++)
			{
				pirates->pirate_array[t] = pirates->pirate_array[t + 1];
			}
			pirates->pirate_array[length-1] = handover_pirate;
		}
		else
		{
			index_count++;
		}
		
	}
	size_t last_treasured_index = (length - treasureless_count - 1);
	if (treasureless_count > 1)
	{
		quicksort_basic(pirates, last_treasured_index + 1, length - 1);
	}
	return last_treasured_index;
}


//This function moves vessel-less pirates to the end, sorts them
//lexicographically by name, and returns the index before the treasureless
//pirates
size_t no_vessel_to_end(pirate_list* pirates)
{
	size_t length = list_length(pirates);
	if (length == 1)
	{
		return 0;
	}
	size_t vesselless_count = 0;
	size_t index_count = 0;
	for (size_t i = 0; i < length; i++)
	{

		pirate* current_pirate = pirates->pirate_array[index_count];
		bool current_p_vessel_change = get_vessel_change(current_pirate);
		if (!current_p_vessel_change)
		{
			vesselless_count++;
			pirate* handover_pirate = pirates->pirate_array[index_count];
			for (size_t t = index_count; t < length-1; t++)
			{
				pirates->pirate_array[t] = pirates->pirate_array[t + 1];
			}
			pirates->pirate_array[length-1] = handover_pirate;
		}
		else
		{
			index_count++;
		}
		
	}
	size_t last_vesseled_index = (length - vesselless_count - 1);
	if (vesselless_count > 1)
	{
		quicksort_basic(pirates, last_vesseled_index + 1, length - 1);
	}
	return last_vesseled_index;
}

//This function reads in the captains and sets them to their respective pirates
void captain_read(pirate_list* pirates, FILE *restrict input)
{
	bool reached_end = false;
	while (!reached_end)
	{
		char* underling = malloc(128 * sizeof(char));
		char* temp_pointer_one = underling;
		underling = fgets(underling, 128, input);
		
		if (underling == NULL)//This should stop it at the end 
		{
			free(underling);
			free(temp_pointer_one);
			return;
		}
		char* captain = malloc(128 * sizeof(char));
		char* temp_pointer_two = underling;
		captain = fgets(captain, 128, input);
			if (captain == NULL)//This should stop it at the end 
		{
			free(captain);
			free(temp_pointer_two);
			return;
		}
		size_t prev_char_count = strcspn(captain, "\n");
		captain[prev_char_count] = '\0';
		size_t prev_char_count_two = strcspn(underling, "\n");
		underling[prev_char_count_two] = '\0';
		pirate* cap_p = list_access(pirates, nti(pirates, captain));
		pirate* und_p = list_access(pirates, nti(pirates, underling));
		set_captain_changed(und_p, true);
		pirate_set_captain(und_p, cap_p);
		free(underling);
		free(captain);
	}
}

//ntp stands for name-to-index
size_t nti(pirate_list *pirates, char* name)
{
	size_t length = list_length(pirates);
    bool pirate_is_stored = false;
	size_t found_index = 0;
    for (int c = 0; c < length; c++)
    {
        if (strcmp(pirate_name(list_access(pirates, c)), name) == 0)
        {
            pirate_is_stored = true;
			found_index = c;
        }
    }
	if (pirate_is_stored == true)
	{
		size_t new_found_index = found_index;
		return new_found_index;
	}
	else
	{
		return 0; //This means you have to be careful if they aren't in the list
	}
}