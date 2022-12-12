#include "chilon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// @brief ANSI Escape code from color ID
/// @param c Color supported from enum
/// @param bgtype 1 if select background, foreground otherwise
/// @return escape sequence for terminal command
char *getcolor(color_t c, int bgtype)
{
    int size = sizeof(char) * 8;
    char *str = malloc(size);
    memset(str, 0, size);
    if (c != NORMAL)
    {
        snprintf(str, size, (bgtype ? "\e[4%dm" : "\e[3%dm"), (int)c);
    }
    else
    {
        snprintf(str, size, "\e[m");
    }
    return str;
}

/// @brief ANSI Escape code from effect ID
/// @param e Effect supported from enum
/// @return escape sequence for terminal command
char *geteffect(effect_t e)
{
    int size = sizeof(char) * 8;
    char *str = malloc(size);
    memset(str, 0, size);
    snprintf(str, size, "\e[%dm", (int)e);
    return str;
}

char* fillarray(char *buffer, int maxwidth, char *value)
{
    memset(buffer, 0, maxwidth);
    strncpy(buffer, value, maxwidth);
    if(strlen(value) < maxwidth)
    {
        for(int j = strlen(buffer); j < maxwidth; j++)
        {
            strncat(buffer, " ", sizeof(char));
        }
    }
    return buffer;
}

void chilon_logo()
{
    printf(" __    ____ _     _ _             \n \\ \\  / ___| |__ (_) | ___  _ __  \n  \\ \\| |   | '_ \\| | |/ _ \\| '_ \\ \n   \\ \\ |___| | | | | | (_) | | | |\n    \\_\\____|_| |_|_|_|\\___/|_| |_|\n                                  \n");
}

void chilon_print(const char *chararray)
{
    printf(chararray);
}

void chilon_draw_table(const char *title, char **rows, int nb_row, char **cols, int nb_col, int* vals, int element_size)
{
    int max_width_col = 8;
    int width_garray = (nb_col+1)*(max_width_col+1)+1;

    color_t crow1 = BLUE;
    color_t crow2 = CYAN;


    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc(max_width_col*sizeof(char));

    // Set first delimiter line
    memset(buffer, 0, width_garray);
    for(int i = 0; i < width_garray; i++)
    {
        if(i%(max_width_col+1) == 0)
        {
            strcat(buffer, "|");
        }
        else
        {
            strcat(buffer, "-");
        }
    }
    chilon_print("\n");
    chilon_cprint(NORMAL, GREEN, BOLD, ".");
    chilon_cprint(NORMAL, GREEN, BOLD, title);
    for(int i = strlen(title)+1; i < width_garray-1; i++)
    {
        chilon_cprint(NORMAL, GREEN, BOLD, "-");
    }
    chilon_cprint(NORMAL, GREEN, BOLD, ".\n");
    
    // Set columns names
    chilon_cprint(NORMAL, GREEN, BOLD, "|");
    fillarray(label_buffer, max_width_col, " ");
    chilon_cprint(GREEN, GREEN, BOLD, label_buffer);
    chilon_cprint(NORMAL, GREEN, BOLD, "|");
    // Set col labels
    for(int i = 0; i < nb_col; i++)
    {
        fillarray(label_buffer, max_width_col, cols[i]);
        chilon_cprint(CYAN, RED, BOLD, label_buffer);
        chilon_cprint(NORMAL, GREEN, BOLD, "|");
    }
    chilon_print("\n");
    chilon_cprint(NORMAL, GREEN, BOLD, buffer);
    chilon_print("\n");

    for(int y = 0; y < nb_row; y++)
    {
        // print label
        chilon_cprint(NORMAL, GREEN, BOLD, "|");
        color_t ccur = crow1;
        if(y%2 == 0)
            ccur = crow2;

        fillarray(label_buffer, max_width_col, rows[y]);
        chilon_cprint(ccur, RED, BOLD, label_buffer);
        chilon_cprint(NORMAL, GREEN, BOLD, "|");
        // print values of cols
        for(int x = 0; x < nb_col; x++)
        {
            int v = *((vals+y*nb_col)+x);
            char temp[max_width_col];
            sprintf(temp, "%d", v);
            fillarray(label_buffer, max_width_col, temp);
            chilon_cprint(ccur, RED, ITALIC, label_buffer);
            chilon_cprint(NORMAL, GREEN, BOLD, "|");
        }
        chilon_print("\n");
    }

    // Last line
    chilon_cprint(NORMAL, GREEN, BOLD, "'");
    for(int i = 1; i < width_garray-1; i++)
    {
        chilon_cprint(NORMAL, GREEN, BOLD, "-");
    }
    chilon_cprint(NORMAL, GREEN, BOLD, "'\n");

    free(label_buffer);
    free(buffer);
}

void chilon_cprint(color_t bg, color_t fg, effect_t effect, char *text)
{
    char* fg_color = getcolor(fg, 0);
    char* bg_color = getcolor(bg, 1);
    char* type_effect = geteffect(effect);
    char* reset = getcolor(NORMAL, 0);

    int size = (strlen(text) + strlen(bg_color) + strlen(fg_color) + strlen(type_effect) + strlen(reset)) * sizeof(char) + 1;
    char *buffer = malloc(size);
    memset(buffer, 0, size);

    snprintf(buffer, size, "%s%s%s%s%s", bg_color, fg_color, type_effect, text, reset);
    chilon_print(buffer);

    free(buffer);
    free(reset);
    free(fg_color);
    free(bg_color);
    free(type_effect);
}