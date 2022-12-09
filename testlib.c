#include <stdio.h>

int array_size = 5;
char* array = "abcdef";

int main(int argc, char* arv[])
{
    for(int i = 0; i < array_size; i++)
    {
        printf("array[%d]=%c \n", i, array[i]);
    }
}