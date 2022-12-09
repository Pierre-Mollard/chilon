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

    free(buff);
}