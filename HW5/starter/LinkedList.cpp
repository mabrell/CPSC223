/*
 * LinkedList.cpp
 * CPSC 223 Pset 5
 *
 * Implementation for Linked List of GNHTA Stations
 * TO STUDENT: Don't forget to remove // TODO when you submit!
 *
 * Author: [YOUR NAME HERE]
 */

#include "LinkedList.h"
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    // TODO: Implement this
}

// Destructor
LinkedList::~LinkedList()
{
    // TODO: Implement this
}

// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    // TODO: Implement assignment operator overload

    // TODO: Remove this line, which is here only so the starter code compiles.
    return *this;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    // TODO: Implement the copy constructor
}

int LinkedList::getLength() const
{
    // TODO: Implement this

    // TODO: Remove this line, which is here only so the starter code compiles.
    return 0;
}

bool LinkedList::isCurrPosNull() const
{
    // TODO: Implement this

    // TODO: Remove this line, which is here only so the starter code compiles.
    return false;
}

void LinkedList::insertStation(Station s)
{
    // TODO: Implement this
}

void LinkedList::removeStation(Station s)
{
    // TODO: Implement this
}

Station LinkedList::getNextStation()
{
    // TODO: Implement this

    // TODO: Remove this line, which is here only so the starter code compiles.
    return Station{};
}

void LinkedList::resetCurrPos()
{
    // TODO: Implement this
}

void LinkedList::makeEmpty()
{
    // TODO: Implement this
}

void LinkedList::print(ostream &out)
{
    // TODO: Implement this
}
