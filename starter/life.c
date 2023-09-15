/* Here we define the implementation of the IsAlive and Should Die Functions*/

#include "life.h"
#include <stdio.h>
#include <stdbool.h> 

bool isAlive(int field[], size_t i, size_t size)
{
    if (field[i] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool shouldDie(int field[], size_t i, size_t size)
{
    if ( i <= 0 || i >= (size - 1))
    {
        return false;
    }
    if (field[i-1] == 1 && field[i+1] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void kill(int currarr[], size_t i){
    currarr[i] = 0;
}

void revive(int currarr[], size_t i){
    currarr[i] = 1;
}