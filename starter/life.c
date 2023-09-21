/* Here we define the implementation of the IsAlive and Should Die Functions*/

#include "life.h"
#include <stdio.h>
#include <stdbool.h> 

//This function determines whether the cell corresponding to the inputted array
//and index is alive, and returns a boolean accordingly
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

//This function determines whether the cell corresponding to the inputted array
//and index should die, and returns a boolean accordingly
bool shouldDie(int field[], size_t i, size_t size)
{
    if ( i <= 0 || i >= 9)
    {
        //printf("should die ran right");
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

//This function intakes an array and index, and kills the corresponding cell
void kill(int currarr[], size_t i)
{
    currarr[i] = 0;
}

//This function intakes an array and index, and revives the corresponding cell
void revive(int currarr[], size_t i)
{
    currarr[i] = 1;
}


//This function is the most complicated of the program, as it calculates and
//updates the entirety of currarr based on what refarr is. This is essentially
//just the rules of the Game of Life turned into a logic structure. So, every
//time the program wants to take a step, it runs this function. This function
//intakes the refarr and currarr and results in a changed currarr.
void evolution(int refarr[], int currarr[], size_t size)
{
    for (int b = 0; b <= size - 1; b++)
        {
            if ((isAlive(refarr, b, size)) && (shouldDie(refarr, b, size) == true))
            {
                kill(currarr, b);
            }
            if (b <= 0)
            {
                if ((!isAlive(refarr, b+1, size)) && isAlive(refarr, b, size))
                {
                    revive(currarr, b+1);
                }
                
                    
                continue;
            }
            if (b >= size - 1)
            {
                if ((!isAlive(refarr, b-1, size)) && isAlive(refarr, b, size))
                {
                    revive(currarr, b-1);
                }
                continue;
            }
            if (isAlive(refarr, b, size))
                if (!isAlive(refarr, b-1, size) || !isAlive(refarr, b + 1, size))
                {
                    if (!isAlive(refarr, b-1, size))
                    {
                        revive(currarr, b-1);
                    }
                    
                    if (!isAlive(refarr, b+1, size)) 
                    {
                        revive(currarr, b+1);
                    }
                }
        }
}
//This function transfers the current array to the reference array for the next
//iteration of the function.
int transfer_to_arrays(int refarr[],int currarr[], size_t c, int init_integer)
{
    currarr[c] = 0;
    refarr[c] = init_integer % 10;
    currarr[c] = init_integer % 10;
    init_integer = (init_integer/10);
    return init_integer;
}