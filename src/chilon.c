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

void chilon_logo()
{
    printf(" __    ____ _     _ _             \n \\ \\  / ___| |__ (_) | ___  _ __  \n  \\ \\| |   | '_ \\| | |/ _ \\| '_ \\ \n   \\ \\ |___| | | | | | (_) | | | |\n    \\_\\____|_| |_|_|_|\\___/|_| |_|\n                                  \n");
}

void chilon_print(const char *chararray)
{
    printf(chararray);
}

void chilon_draw_table(const char *title, int rows, int cols)
{
    printf("------ todo\n");
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