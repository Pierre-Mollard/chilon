#include "chilon.h"
#include <stdlib.h>

void chilon_clear_screen(unsigned int mode)
{
    switch (mode)
    {
    case 0:
        chilon_print("\e[0J");
        break;
    case 1:
        chilon_print("\e[1J");
        break;
    case 2:
        chilon_print("\e[2J");
        break;
    case 3:
        chilon_print("\e[3J");
        break;
    default:
        chilon_print("Clearing screen failed, wrong argument \n");
        break;
    }
}

void chilon_clear_line(unsigned int mode)
{
    switch (mode)
    {
    case 0:
        chilon_print("\e[0K");
        break;
    case 1:
        chilon_print("\e[1K");
        break;
    case 2:
        chilon_print("\e[2K");
        break;
    default:
        chilon_print("Clearing line failed, wrong argument \n");
        break;
    }
}

void chilon_set_cursor_pos(unsigned int x, unsigned int y)
{
    size_t needed = snprintf(NULL, 0, "\e[%u;%uH", x, y) + 1;
    char  *buffer = malloc(needed);
    sprintf(buffer, "\e[%u;%uH", x, y);
    chilon_print(buffer);
    free(buffer);
}

void chilon_move_cursor(unsigned int direction, unsigned int amount)
{
    char d;
    switch (direction)
    {
    case 0:
        d = 'A';
        break;
    case 1:
        d = 'B';
        break;
    case 2:
        d = 'C';
        break;
    case 3:
        d = 'D';
        break;
    default:
        chilon_print("Moving cursor failed, wrong argument \n");
        return;
        break;
    }

    size_t needed = snprintf(NULL, 0, "\e[%u%c", amount, d) + 1;
    char  *buffer = malloc(needed);
    sprintf(buffer, "\e[%u%c", amount, d);
    chilon_print(buffer);
    free(buffer);
}

void chilon_set_cursor_line(unsigned int direction, unsigned int amount)
{
    char d;
    switch (direction)
    {
    case 0:
        d = 'E';
        break;
    case 1:
        d = 'F';
        break;
    default:
        chilon_print("Moving cursor failed, wrong argument \n");
        return;
        break;
    }

    size_t needed = snprintf(NULL, 0, "\e[%u%c", amount, d) + 1;
    char  *buffer = malloc(needed);
    sprintf(buffer, "\e[%u%c", amount, d);
    chilon_print(buffer);
    free(buffer);
}

void chilon_set_cursor_column(int x)
{
    size_t needed = snprintf(NULL, 0, "\e[%uG", x) + 1;
    char  *buffer = malloc(needed);
    sprintf(buffer, "\e[%uG", x);
    chilon_print(buffer);
    free(buffer);
}

void chilon_scroll(unsigned int direction, unsigned int nb_page)
{
    char d;
    switch (direction)
    {
    case 0:
        d = 'T';
        break;
    case 1:
        d = 'S';
        break;
    default:
        chilon_print("Scrolling page failed, wrong argument \n");
        return;
        break;
    }

    size_t needed = snprintf(NULL, 0, "\e[%u%c", nb_page, d) + 1;
    char  *buffer = malloc(needed);
    sprintf(buffer, "\e[%u%c", nb_page, d);
    chilon_print(buffer);
    free(buffer);
}