

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

//Transfer the strings to independent
char* transfer_string(char* input)