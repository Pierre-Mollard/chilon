#include "src/chilon.h"
#include <stdio.h>
#include <stdlib.h>

int array_size = 5;
char* array = "abcdef";

/// @brief Rainbow 'color' palette {fg, bg, effect}
color_palette_t rainbow_palette = {
    {RED, NORMAL, FBLINK},       //title
    {MAGENTA, NORMAL, BOLD},      //borders
    {YELLOW, GREEN, BOLD},       //name_col
    {BLUE, CYAN, BOLD},      //name_row_even
    {CYAN, BLUE, BOLD},       //name_row_uneven
    {WHITE, RED, ITALIC},    //data_row_even
    {RED, WHITE, ITALIC}      //data_row_uneven
};

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

    char *rows[8] = {"attr1", "attr2", "attr3", "attr4", "attr5", "attr6", "attr7", "attr8"};
    char *cols[5] = {"CASE 1", "CASE 2", "CASE 3", "CASE 4", "CASE 5"};
    int values[8][5] = {{0, 1, 2, 3, 4}, {10, 11, 12, 13, 14}, {20, 21, 22, 23, 24}, {30, 31, 32, 33, 34}, {40, 41, 42, 43, 44}, {50, 51, 52, 53, 54}, {60, 61, 62, 63, 64}, {70, 71, 72, 73, 74}};
    chilon_draw_table("Test Graphical Array", rows, 8, cols, 5, (int*)values, 6);
    chilon_draw_ctable("Test Graphical Array", rows, 8, cols, 5, (int*)values, 6, &rainbow_palette);

    free(buff);
}