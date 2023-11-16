/*
 * Station.cpp
 * CPSC 223 Pset 5
 *
 * Implementation of the Station class
 * TO STUDENT: Don't forget to remove // TODO before you submit!
 *
 * Author: Mason Abrell
 * CPSC 223 - Pset 5
 * Date: 11/16/2023
 * Implementation of Station, with class methods defined
 */

#include "Station.h"
#include <iostream>
using namespace std;




// Default Constructor (Implemented for you)
Station::Station()
{
    this->name = "NoName";
    this->access = false;
}

//Paramatrized Constructor
Station::Station(string name, bool access)
{
	this->name = name;
	this->access = access;
}

//Other public functions

bool Station::isEqual(Station s)
{
	int result = this->name.compare(s.getName());
	bool same_access = false;
	if (this->access == s.access)
	{
		same_access = true;
	}
	
	if ((result == 0) && (same_access == true))
	{
		return true;
	}
	
    return false;
}

void Station::print(ostream &outfile)
{
	char access_indic;
	if (this->access == true)
	{
		access_indic = 'A';
	}
	else
	{
		access_indic = 'U';
	}
    outfile << this->name << " " << access_indic;
}

