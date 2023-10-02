

struct suspicious_pirate { //I named it suspicious pirate bc they're hiding
                            //behind an opaque construct!
    char* name;
    char* rank_name;
    char* vessel_name;
    char* port_name;
    size_t treasure_amount;
    char* skills;

}

/**
 * Allocates enough memory for a pirate, and returns a pointer to the newly-
 *  allocated memory.
 */
pirate *pirate_create(char* name, char* rank_name ,char* vessel_name, char* port_name,
size_t treasure_amount, char* skills){
    pirate *new_p = malloc(sizeof(pirate));
    new_p->name = name;
    new_p->rank_name = rank_name;
    new_p->vessel_name = vessel_name;
    new_p->port_name = port_name;
    new_p->treasure_amount = treasure_amount;
    new_p->skills
}

/**
 * Reads a pirate profile from input. Assumes that the input cursor is at the
 *  beginning of a pirate profile (otherwise, its behavior is undefined).
 *
 * Returns a pointer to a pirate created from the profile in input.
 *
 * This function consumes a blank line after the end of the current profile
 *  before returning, meaning that after this function is done, the input
 *  cursor is either at the end of the input file or at the beginning of the
 *  next pirate profile.
 */
pirate *pirate_read(FILE *input); //NOTE THIS IS ONLY FOR NAMES
{
    int *new_pirate_name = calloc(127, sizeof(char)) //may fail bc blank space
    fgets(*new_pirate_name, 127, *input)
    int *new_pirate_pointer = pirate_create(*new_pirate_name) //NOTE: passing p
    return new_pirate_pointer
}

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 */
void pirate_print(const pirate *p, FILE *output);

/**
 * Returns the name of the pirate.
 */
const char *pirate_name(const pirate *p)
{
    char* desired_pirate_name = *p.name;
    return desired_pirate_name;
}

/**
 * Sets the name of a pirate.
 */
void pirate_set_name(pirate *p, const char *name) //Am I missing something here?
{
    *p.name = *name;
}

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 */
int pirate_compare(pirate *a, pirate *b);

/**
 * Frees all memory associated with this pirate. This function claims ownership
 *  of p.
 */
void pirate_destroy(pirate *p)
{
    free(p->name);
    free(rank_name);
    free(p->vessel_name);
    free(p->port_name);
    free(p->treasure_amount);
    free(p->skills);
    free(p)
}