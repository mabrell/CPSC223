/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Mason Abrell
*/

#include "life.h"
#include "helpers.h"
#include <stdio.h>

// TO STUDENT: Do not change this definition!
#ifndef SIZE
#define SIZE 10
#endif
// End modification restriction


int main(int argc, char *argv[])
{
    //printf('%d', SIZE)
    int time_steps = atoi(argv[1]); 
    int refarr[SIZE]; //Here, arrays are initialized & inputs assigned
    int currarr[SIZE];
    int init_integer = atoi(argv[2]);

    for (int c = (SIZE - 1); c >= 0; c--) //Integer input transferred to array
    {
        init_integer = transfer_to_arrays(refarr,currarr, c, init_integer);
    }
    print_initial(refarr, SIZE); //Initial value printed

    for (int s = 0; s <= time_steps - 1; s++ ) //Loop for # of time_steps
    {
        evolution(refarr, currarr, SIZE);  //Function updates currarr based on refarr
        for (int c = 0; c <= (SIZE - 1); c++){ //currarr gets copied onto refarr
            if (currarr[c] == 1)
            {
                refarr[c] = 1;
            }
            if (currarr[c] == 0)
            {
                refarr[c] = 0;
            }
        }
        print_generation(currarr, s+1, SIZE); //new generation is printed
        
    }
    return 0;
}