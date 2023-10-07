#include "libhookbook.h"
#include "pirate.h"
#include "pirate_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

//Checks for the right number of arguements, true if correct, false if not
bool validity_check_a( int argc)
{
    if (argc < 2) //Ensures user inputs 2 arguements
    {
        return false;
    }
    else
        return true;
}


//CHecks for an accessible file, true if correct, false if not
bool validity_check_b(char* file_name)
{
    int access_marker = access(file_name, F_OK);
	access_marker = access_marker + access(file_name, R_OK);
    if (access_marker != 0) //Ensures file is accessible and readable
    {
        return false;
    }
    else
        return true;
}

bool big_validity_check (int argc, char* file_name)
{
	bool test_a = validity_check_a(argc);
	if (test_a == false)
	{
		return false;
	}
	bool test_b = validity_check_b(file_name);
	if (test_b == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}