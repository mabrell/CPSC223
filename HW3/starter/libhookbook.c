#include "libhookbook.h"
#include "pirate_list.h"
#include <stdio.h>
#include <stdbool.h>

//Does a total validity check
int total_validity_check(size_t argc,char* argv1, char* argv2, char* argv3)
{
	bool valid_argc = argc_validity_check(argc);
	if (!valid_argc)
	{
		return 1;
	}
	if (argc == 3)
	{
		bool valid = argc3_validity_check(argv1, argv2);
		if (!valid)
		{
			return 1;
		}

	}
	if (argc == 4)
	{
		bool valid = argc4_validity_check(argv1, argv2, argv3);
		if (!valid)
		{
			return 1;
		}
	}
	return 0;
}

//Checks for the right number of arguements, true if correct, false if not
bool argc_validity_check(int argc)
{
    if (argc < 3) //Ensures user inputs 2 arguements
    {
		fprintf(stderr, "(not enough arguments) \n");
        return false;
    }
	if (argc > 4)
	{
		fprintf(stderr, "(too many arguments) \n");
		return false;
	}

    return true;
}

//Checks the validity of a 3 argument input
bool argc3_validity_check(char* argv1, char* argv2)
{
	if ((argv1[0] == '-') || (argv2[0] == '-'))
	{ //This means that this is a flag
		fprintf(stderr, "(not enough filenames) \n");
		return false;
	}
	
	bool argv1_access = validity_check_b(argv1);
	bool argv2_access = validity_check_b(argv2);
	if (!(argv1_access) || !(argv2_access))
	{
		fprintf(stderr, "(file doesn't exist) \n");
		return false;
	}
	
	else
	{
		return true;
	}
}

//Checks the validity of a 4 argument input
bool argc4_validity_check(char* argv1, char* argv2, char* argv3)
{
	char* file1 = "fakefile1";
	char* file2 = "fakefile2";
	bool flag_exists = false;
	if (argv1[0] == '-')
	{ //This means that this is a flag
		char flag = argv1[1];
		if ((flag != 'v') && (flag != 't') && (flag != 'n'))
		{
			fprintf(stderr, "(invalid sort flag: %s \n)", argv1);
			return false;
		}
		else
		{
			flag_exists = true;
			file1 = argv2;
			file2 = argv3;
		}
	}
	
	if (argv2[0] == '-')
	{ //This means that this is a flag
		char flag = argv2[1];
		if ((flag != 'v') && (flag != 't') && (flag != 'n'))
		{
			fprintf(stderr, "(invalid sort flag: %s \n)", argv2);
			return false;
		}
		else
		{
			flag_exists = true;
			file1 = argv1;
			file2 = argv3;
		}
	}
	if (argv3[0] == '-')
	{ //This means that this is a flag
		char flag = argv3[1];
		if ((flag != 'v') && (flag != 't') && (flag != 'n'))
		{
			fprintf(stderr, "(invalid sort flag: %s) \n", argv3);
			return false;
		}
		else
		{
			flag_exists = true;
			file1 = argv1;
			file2 = argv2;
		}
	}
	if (!flag_exists)
	{
		fprintf(stderr, "(too many filenames) \n");
		return false;
	}
	
	bool argv1_access = validity_check_b(file1);
	bool argv2_access = validity_check_b(file2);
	if (!(argv1_access) || !(argv2_access))
	{
		fprintf(stderr, " (file doesn't exist) \n");
		return false;
	}
	else
	{
		return true;
	}

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

//This function intakes the arguements for an argc3 input, processes them,
//and returns a correspondingly created pirate list.
pirate_list* argc4_p(char* argv1, char* argv2, char* argv3, int (*name_comp)(const void *, const void *), int (*treasure_comp)(const void *, const void *), int (*vessel_comp)(const void *, const void *))
{
	char flag = 'n';
	if (argv1[0] == '-')
	{ //This means that this is a flag
		flag = argv1[1];
	}
	
	if (argv2[0] == '-')
	{ //This means that this is a flag
		flag = argv2[1];
	}

	if (argv3[0] == '-')
	{ //This means that this is a flag
		flag = argv3[1];
	}

	// else
	// {
	// 	flag = 'n';
	// }

	pirate_list* new_pirate_list;

	if (flag == 'n')
	{
		new_pirate_list = list_create(name_comp);
		set_sort_type(new_pirate_list, 'n');
	}
	if (flag == 'v')
	{
		new_pirate_list = list_create(vessel_comp);
		set_sort_type(new_pirate_list, 'v');
	}
	if (flag == 't')
	{
		new_pirate_list = list_create(treasure_comp);
		set_sort_type(new_pirate_list, 't');
	}
	else
	{
		//new_pirate_list = list_create(name_comp);
	}
	return new_pirate_list;
}

FILE* argc4_prcs_pirate_file(char* argv1, char* argv2, char* argv3)
{
	char* file1 = "fakefile";
	if (argv1[0] == '-')
	{ //This means that this is a flag
		file1 = argv2;
	}
	
	if (argv2[0] == '-')
	{ //This means that this is a flag
		file1 = argv1;
	}

	if (argv3[0] == '-')
	{ //This means that this is a flag
		file1 = argv1;
	}
	FILE *fptr = fopen((const char *) file1, "r");
	return fptr;
}

//returns argc4 captain file
FILE* argc4_prcs_captn_file(char* argv1, char* argv2, char* argv3)
{
	char* file2 = "fake_file";
	if (argv1[0] == '-')
	{ //This means that this is a flag
		file2 = argv3;
	}
	
	if (argv2[0] == '-')
	{ //This means that this is a flag
		file2 = argv3;
	}

	if (argv3[0] == '-')
	{ //This means that this is a flag
		file2 = argv2;
	}

	FILE *fptr = fopen((const char *) file2, "r");
	return fptr;
}

char argc4_prcs_flag(char* argv1, char* argv2, char* argv3)
{
	char flag = 'n';

	if (argv1[0] == '-')
	{ //This means that this is a flag
		flag = argv1[1];
	}
	
	if (argv2[0] == '-')
	{ //This means that this is a flag
		flag = argv2[1];
	}

	if (argv3[0] == '-')
	{ //This means that this is a flag
		flag = argv3[1];
	}
	
	// else
	// {
	// 	flag = 'n';
	// }

	return flag;
}

void pirate_read_and_sort(FILE* fptr, FILE* cpt, pirate_list* new_pirate_list)
{
	bool EOF_reached = false;
	while (!EOF_reached)
	{
		pirate* new_pirate_pointer = pirate_read(fptr);
		if (new_pirate_pointer == NULL)
		{
			EOF_reached = true;
		}
		else
		{
			pirate* p = list_insert(new_pirate_list, new_pirate_pointer, 0);
			if (p != NULL)
			{
				pirate_destroy(p);
			}
			
		}
	}
	list_sort(new_pirate_list);
	captain_read(new_pirate_list, cpt);
}

//prints the entire inputted pirate list
void print_whole_list(pirate_list* new_pirate_list)
{
	size_t length = list_length(new_pirate_list);
	for (size_t i = 0; i < length; i++)
	{
		pirate_print(list_access(new_pirate_list, i), stdout);
	}
}

//Closes files and destroys list
void clean_up(FILE* fptr, FILE* fptr_two, pirate_list* lst)
{
	fclose(fptr);
	fclose(fptr_two);
	list_destroy(lst);
}