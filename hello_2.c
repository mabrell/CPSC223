#include <stdio.h>

int main(int argc, char *argv[]){

    char name[127];
    printf("Enter your name: ");
    scanf("%[^\n]s", name);
    printf("Hello, %s!\n", name);
    return 0;
}