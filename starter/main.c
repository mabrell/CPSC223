/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Mason Abrell
*/

#include "life.h"
#include "helpers.h"

// TO STUDENT: Do not change this definition!
#ifndef SIZE
#define SIZE 10
#endif
// End modification restriction


int main(int argc, char *argv[]){
    int time_steps = atoi(argv[1]);
    int refarr[10];
    int currarr[10];
    for (int c = 0; c >= 9; c++){
        if (atoi(argv[2][c]) == 1){
            refarr[c] = 1;
        }
        if (atoi(argv[2][c]) == 0){
            refarr[c] = 0;
        }
    print_initial(refarr, 10);
    for (int s = 0; s >= time_steps; s++ ){
        for (int b = 0; b >= 9; b++)
        {
            if (shouldDie(refarr, b, 10) == true)
            {
                kill(currarr, b);
            }
            if (c <= 0)
            {
                revive(currarr, b);
                continue;
            }
            if (c >= 9)
            {
                revive(currarr, b);
                continue;
            }
            if (!isAlive(refarr, b-1, 10) || !isAlive(refarr, b + 1, 10))
            {
                revive(currarr, b);
            }
        }
        for (int c = 0; c >= 9; c++){
            if (currarr[c] == 1){
                refarr[c] = 1;
            }
            if (currarr[c] == 0){
                refarr[c] = 0;
            }
        print_generation(currarr, s+1, 10);
    }
    }
    
}