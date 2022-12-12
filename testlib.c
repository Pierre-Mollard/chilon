#include "src/chilon.h"
#include <stdio.h>
#include <stdlib.h>

int array_size = 5;
char* array = "abcdef";

int main(int argc, char* arv[])
{
    char * buff = (char*) malloc(64);

    chilon_logo();

    for(int i = 0; i < array_size; i++)
    {
        sprintf(buff, "array[%d]=%c \n", i, array[i]);
        chilon_print(buff);
    }

    for(int i = 0; i < 60; i++)
    {
        printf("\e[%dmTESTING [%d] \e[m \n", i, i);
    }

    chilon_cprint(YELLOW, RED, BOLD, "this text should be bold red on yellow");
    printf("\nthis on should be normal \n");
    printf("this on should be normal \n");
    printf("this on should be normal \n");

    free(buff);
}