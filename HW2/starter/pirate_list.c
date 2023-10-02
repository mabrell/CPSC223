

typedef struct
{
    size_t length;
    size_t capacity;
    int *pirate_array;
}pirate_instance_t; //Should this be pirate instance t??

pirate_list *list_create()
{
    pirate_list *pirate_instance_t = malloc(sizeof(pirate_instance_t));
    *pirate_instance_t->length = 0;
    *pirate_instance_t->capacity = INITIAL_CAPACITY;
    *pirate_instance_t->pirate_array = calloc(capacity, sizeof(*char)) //are diff pointers diff sizes??
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
        fprintf(stderr, "Expand to %zu\n", new_capacity); //WHAT IS STDERR??
    }
    
        
}


void list_contract_if_necessary(pirate_list *pirates)
{
    if ((list_length(*pirates) < (*pirates.capacity / 4)))
    {
        *pirates.capacity = (*pirates.capacity) / 2;
        int new_capacity = *pirates.capacity;
        *pirates.pirate_array = realloc(*pirate_array, sizeof(*pirates.capacity * sizeof(char*)));
        fprintf(stderr, "Contract to %zu\n", new_capacity); //WHAT IS STDERR??
    }
}

size_t list_index_of(pirate_list *pirates, pirate *p)
{
    size_t list_length = *pirates.length;
    size_t correct_pirate = (list_length + 36);
    for (int c = 0; c <= list_length; c++) //Is this <= ok?
    {
        if (compareArray(*pirates.pirate_array[c], *p))
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