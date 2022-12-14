#include "src/chilon.h"
#include <stdio.h>
#include <stdlib.h>

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
    int array_size = 8;
    long int array[array_size][3];
    float arrayf[array_size][3];

    chilon_logo();

    for(int i = 0; i < array_size; i++)
    {
        array[i][0] = i;
        array[i][2] = (long int)&array[i][1];
        array[i][1] = i*i;

        arrayf[i][0] = i*0.1;
        arrayf[i][2] = i;
        arrayf[i][1] = (i/(float)(array_size-1))*100;
    }

    char *rows[8] = {"attr1", "attr2", "attr3", "attr4", "attr5", "attr6", "attr7", "attr8"};
    char *cols[5] = {"CASE 1", "CASE 2", "CASE 3", "CASE 4", "CASE 5"};
    int values[8][5] = {{0, 1, 2, 3, 4}, {10, 11, 12, 13, 14}, {20, 21, 22, 23, 24}, {30, 31, 32, 33, 34}, {40, 41, 42, 43, 44}, {50, 51, 52, 53, 54}, {60, 61, 62, 63, 64}, {70, 71, 72, 73, 74}};
    chilon_draw_table("Test Graphical Array NOCOLOR", rows, 8, cols, 5, values, 6, chilon_iter_INT);
    
    int values2[6][3] = {{0, 1, 2}, {20, 21, 22}, {40, 41, 42}, {50, 51, 52}, {60, 61, 62}, {70, 71, 72}};
    chilon_draw_ctable("Test Graphical Array Smaller", rows, 6, cols, 3, values2, 6, chilon_iter_INT, &rainbow_palette);

    char *rows2[8] = {"attr1", "attr2", "attr3", "attr4", "attr5", "attr6", "attr7", "attr8"};
    char *cols2[3] = {"index", "value", "address"};
    chilon_draw_ctable("Compare addr of long array", rows2, array_size, cols2, 3, array, 16, chilon_iter_LONG, &rainbow_palette);

    char *rows3[8] = {"no0", "no1", "no2", "no3", "no4", "no5", "no6", "no7"};
    char *cols3[3] = {"index*0.1", "percentage", "index"};
    chilon_draw_ctable("Compare addr of float array \a", rows3, array_size, cols3, 3, arrayf, 16, chilon_iter_FLOAT, &rainbow_palette);

    printf("\n== TESTING PRINTS METHODS == \n");
    chilon_print("Print with chilon_print, nothing else \n");
    chilon_printf("Print with chilon_printf, with format d=%d, lf=%lf, s=%s, u=%u \n", 42, 12.8, "string", 5);
    chilon_cprint(YELLOW, GREEN, ITALIC, "Print with chilon_cprint, with colors");
    chilon_cprint2(&rainbow_palette.name_row_even, "\nPrint with chilon_cprint2, with font");
    chilon_cprintf(YELLOW, GREEN, ITALIC, "\nPrint with chilon_cprintf, with color & format d=%d, lf=%lf, s=%s, u=%u", 42, 12.8, "string", 5);
    chilon_cprintf2(&rainbow_palette.name_row_even, "\nPrint with chilon_cprintf, with font & format d=%d, lf=%lf, s=%s, u=%u", 42, 12.8, "string", 5);
    printf("\n\n");

    free(buff);
}