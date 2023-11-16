/*
 * LinkedList.cpp
 * CPSC 223 Pset 5
 *
 * Implementation for Linked List of GNHTA Stations
 * TO STUDENT: Don't forget to remove // TODO when you submit!
 *
 * Author: Mason Abrell
 * CPSC 223 - Pset 5
 * Date: 11/16/2023
 * Linked List Implementation
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

//Destroys the current node, returns a pointer to the next node, unless NULL, in
//which case returns null
NodeType* node_destroy(NodeType* target)
{
	NodeType* temp = target->next;
	delete(target);
	return temp;
}

//Destroys entire linked list (that is the nodes that compose it)
/**Sets the initial pointer to the first node to null
 * @param NodeType* first is a pointer to the first node of the target list 
 * 
 */
void node_list_destroy(NodeType* first)
{
	NodeType* current_node = first;
	first = NULL;
	bool found_end = false;
	while (found_end == false)
	{
		current_node = node_destroy(current_node);
		if (current_node == NULL)
		{
			found_end = true;
		}
		
	}
	return;
}

// Default constructor
LinkedList::LinkedList()
{
   this->currPos = NULL;
   this->length = 0;
   this->head = NULL;

}

// Destructor
LinkedList::~LinkedList()
{
    this->makeEmpty();
	this->currPos = NULL;
	this->head = NULL;
}

// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if (this == &rhs) {
		return *this;
	}

	this->makeEmpty();
	currPos = NULL;
	head = NULL;
	
	length = rhs.length;

	if (rhs.length == 0)
	{
		currPos = NULL;
		head = NULL;
		return *this;
	}
	currPos = NULL;
	NodeType* rhs_current;
	rhs_current = rhs.head;
	head = new NodeType;
	head->info = rhs_current->info;
	NodeType* building_current = head;
	while (rhs_current->next != nullptr)
	{
		rhs_current = rhs_current->next;
		NodeType* new_node = new NodeType;
		new_node->next = NULL;
		new_node->info = rhs_current->info;
		building_current->next = new_node;
		
		if (rhs.currPos == rhs_current)
		{
			currPos = new_node;
		}

		building_current = new_node;
	}

    return *this;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
	length = other.length;

	if (other.length == 0)
	{
		currPos = NULL;
		head = NULL;
		return;
	}
	currPos = NULL;
	NodeType* other_current;
	other_current = other.head;
	head = new NodeType;
	head->info = other_current->info;
	NodeType* building_current = head;
	while (other_current->next != nullptr)
	{
		other_current = other_current->next;
		NodeType* new_node = new NodeType;
		new_node->next = NULL;
		new_node->info = other_current->info;
		building_current->next = new_node;
		
		if (other.currPos == other_current)
		{
			currPos = new_node;
		}

		building_current = new_node;
	}
}

int LinkedList::getLength() const
{
	return this->length;
	
    return 0;
}

bool LinkedList::isCurrPosNull() const
{
	if (this->currPos == NULL)
	{
		return true;
	}
	
    return false;
}

//Inserts Station into Linked List
void LinkedList::insertStation(Station s)
{
	NodeType* new_node = new NodeType;
	new_node->info = s;
	NodeType* temp_first = this->head;
	new_node->next = temp_first;
	this->head = new_node;
	this->length++;
	
	return;
}


//removes given station from LinkedList
void LinkedList::removeStation(Station s)
{
	NodeType* previous = NULL;
	NodeType* current_node = this->head;

	while (current_node != NULL)
	{

		bool result = s.isEqual(current_node->info);
		
		if (result == true)
		{

			if ((this->currPos != NULL) && (this->currPos->info.isEqual(s)))
			{
				this->resetCurrPos();
			}
			
			if (current_node == this->head)
			{
				this->head = node_destroy(current_node);
				this->length--;
				break;
			}
			else
			{
				previous->next = node_destroy(current_node);
				this->length--;
				break;
			}
			
		}

		previous = current_node;
		current_node = current_node->next;
	}
	return;
}

Station LinkedList::getNextStation()
{
    if (this->currPos == NULL)
	{
		if (this->head == NULL)
		{
			return Station{};
		}
		
		this->currPos = this->head->next;
		return this->head->info;
	}
	else
	{
		Station temp_two = this->currPos->info;
		this->currPos = this->currPos->next;
		return temp_two;
	}
    return Station{};
}

void LinkedList::resetCurrPos() //This resets the head to NULL
{
    this->currPos = NULL;
	return;
}

void LinkedList::makeEmpty()
{
	if (this->length == 0)
	{
		return;
	}
	
    node_list_destroy(this->head); //Is this dereferencing correctly?
	this->length = 0;
}

void LinkedList::print(ostream &out)
{
    NodeType* current_node = this->head;
	bool found_end = false;
	int i = 0;
	if (this->getLength() == 0)
	{
		out << '\n';
		return;
	}
	
	while (found_end == false)
	{
		if (current_node == NULL)
		{
			found_end = true;
			break;
		}

		if (current_node->next != NULL)
		{
			current_node->info.print(out);
			out << " " << (this->getLength() - i -1) << " == ";
		}
		else
		{
			current_node->info.print(out);
			out << " " << (this->getLength() - i -1) << '\n';
		}
		i++;
		
		current_node = current_node->next;
		if (current_node == NULL)
		{
			found_end = true;
		}
	}
	return;
}

