

//Checks for the right number of arguements
bool validity_check_a( int argc)
{
    if (argc != 2) //Ensures user inputs 2 arguements
    {
        return false
    }
    else
        return true
}


//CHecks for an accessible file
bool validity_check_b(char* file_name)
{
    int access_marker = access(file_name)
    if (access_marker != 0) //Ensures file is accessible and readable
    {
        return false
    }
    else
        return true
}






//Read and store all values for the input file, returning the pointer to a list
pirate_list* read_file_and_store(FILE *file_pointer)
{
    pirate_list* pirate_list_pointer = list_create();
    size_t counter = 0;
    
    bool blank_line = check_blank(temp_array); ///iswhitespace()
    if (!blank_line)
    {
        *pirate_list_pointer.pirate_array[counter] = pirate_read(*file_pointer); //Should there be a * in front of the function?
        if !(*pirate_list_pointer.pirate_array[counter] != (NULL || -1 || 0))
        {
            counter++;//Use return of fgets to decide what to do, if return null or newline, use destroy pirate
        }
    }
    return pirate_list_pointer;
}