#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "skills_list.h"


typedef struct list_node node;


//Structure for the node
struct list_node {

	char* skill_name;
	size_t proficiency;
	node *next;
};


//Structure for the skills list
struct skills_list_instance_t {
    size_t length;
	node *head;
};

//Creates a skills list and returns the pointer to it
skills_list* skills_list_create()
{
	skills_list *new_skills_list = malloc(sizeof(skills_list));
	new_skills_list->length = 0;
	new_skills_list->head = NULL;
	return new_skills_list;
}

void node_destroy(node* target)
{
	free(target->skill_name);
	free(target);
}

//destroys a skills list and all members of the linked list stored inside of it
void skills_list_destroy(skills_list* target)
{
	if (skills_list_length(target) != 0)
	{
		for (size_t i = 0; i < skills_list_length(target); i++)
		{
			node* current = target->head;
			target->head = current->next; //Do this to stitch after breaking
			node_destroy(current);
		}
		
	}
	free(target);
}


//Gets the length of an inputted skills list
size_t skills_list_length(skills_list* skills_scroll)
{
	return skills_scroll->length;
}


//Stiches in a node in between two other pre-existing nodes (should work for 0)
void stich(node* before, node* new_node)
{
	node* after = before->next;
	before->next = new_node;
	new_node->next = after;

}


node* node_create(char* new_skill_name)
{
	node* new_node = malloc(sizeof(node));
	new_node->skill_name = malloc(128 * sizeof(char));
	strcpy(new_node->skill_name, new_skill_name);
	new_node->proficiency = 1;
	new_node->next = NULL;
	return new_node;
}

//getter for the name of the first skill (For testing)
char* get_first_name(skills_list* skills_scroll)
{
	node* current = skills_scroll->head;
	return current->skill_name;
}




//Appends a skill to a skill list, should sort lexicographically
void skills_list_append(skills_list* skills_scroll, char* skill_name)
{
	// if (skills_scroll->length == 1)
	// {
	// 	printf("It's NULL babyyy");
	// }
	
	node* current = skills_scroll->head; //Assigning the pointer to head node
	node* previous_node = skills_scroll->head;
	size_t temp_skills_size = skills_list_length(skills_scroll);
	for (size_t i = 0; i < skills_list_length(skills_scroll); i++)
	{
		int comparison_return = strcmp(skill_name, current->skill_name);
		if ((comparison_return < 0))
		{
			node* new_node = node_create(skill_name);
			if (i == 0)
			{
				node* temp_first_node = skills_scroll->head;
				skills_scroll->head = new_node;
				new_node->next = temp_first_node;
			}
			else
			{
				stich(previous_node, new_node);
			}
			skills_scroll->length++;
			i = skills_list_length(skills_scroll);
			
		}
		if (comparison_return == 0)
		{
			current->proficiency++;
			i = skills_list_length(skills_scroll);
		}
		else if ((i == temp_skills_size - 1))
		{
			node* new_node = node_create(skill_name);
			// if (i == 0)
			// {
			// 	node* temp_first_node = skills_scroll->head;
			// 	skills_scroll->head = new_node;
			// 	new_node->next = temp_first_node;
			// }
			// else
			// {
			// 	stich(current, new_node);
			// }
			stich(current, new_node);
			skills_scroll->length++;
			i = skills_list_length(skills_scroll);
		}

		previous_node = current;
		current = current->next;
	}
	if (skills_list_length(skills_scroll) == 0)
	{
		node* very_first_node = node_create(skill_name);
		skills_scroll->head = very_first_node;
		skills_scroll->length++;
	}
	
}


//removes the first node of the linked list, if there are no nodes, does nothing
void skills_list_remove(skills_list* skills_scroll)
{
	if (skills_list_length(skills_scroll) != 0)
	{
		node* target = skills_scroll->head;
		skills_scroll->head = target->next;
		node_destroy(target);
		skills_scroll->length--;
	}
}

void skills_list_print(skills_list* skills_scroll, FILE *restrict output)
{
	if (skills_scroll->length != 0)
	{
		node* current = skills_scroll->head;
		
		for (size_t i = 0; i < (skills_list_length(skills_scroll)); i++)
		{
			char *temp_skill_name = current->skill_name;
			size_t temp_proficiency = current->proficiency;
			if (i == 0)
			{
				fprintf(output, "    Skills: %s ", temp_skill_name);
				for (size_t i = 0; i < (temp_proficiency - 1) ; i++)
				{
					fprintf(output, "*");
				}
				fprintf(output, "\n");
			}
			else
			{
				fprintf(output, "            %s ", temp_skill_name);
				for (size_t i = 0; i < (temp_proficiency - 1) ; i++)
				{
					fprintf(output, "*");
				}
				fprintf(output, "\n");
			}
			current = current->next;
		}
		
	}
	
	
}
