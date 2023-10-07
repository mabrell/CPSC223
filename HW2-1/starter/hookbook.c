#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	if (!validity_check_a(argc))
    {
        return 1;
    }
    if (!validity_check_b(argv[1]))
    {
        return 1;
    }
	pirate_list* main_pirate_list = list_create();
	FILE *fptr = fopen((const char *) argv[1], "r");
	bool end_reached = false;
	while (end_reached == false)
	{
		pirate* handover = pirate_read(fptr);
		if (handover == NULL)
		{
			end_reached = true;
		}
		else
		{
			list_insert(main_pirate_list, handover, 0);
		}
	}
	list_sort(main_pirate_list);

	for (int c = 0; c < list_length(main_pirate_list); c++)
	{
		pirate_print(list_access(main_pirate_list, c), stdout);
	}
	list_destroy(main_pirate_list);
	fclose(fptr);
	return 0;
}