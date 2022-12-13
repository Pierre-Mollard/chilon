#include "chilon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// @brief Default 'color' palette white and black {fg, bg, effect}
color_palette_t default_palette = {
    {WHITE, NORMAL, BOLD},       //title
    {WHITE, NORMAL, BOLD},      //borders
    {BLACK, WHITE, BOLD},       //name_col
    {WHITE, NORMAL, BOLD},      //name_row_even
    {BLACK, WHITE, BOLD},       //name_row_uneven
    {WHITE, NORMAL, ITALIC},    //data_row_even
    {BLACK, WHITE, ITALIC}      //data_row_uneven
};

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
            strncat(buffer, " ", sizeof(" "));
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
    printf("%s", chararray);
}

void chilon_draw_table(const char *title, char **rows, int nb_row, char **cols, int nb_col, int* vals, int element_width)
{
    chilon_draw_ctable(title, rows, nb_row, cols, nb_col, vals, element_width, &default_palette);
}

void chilon_draw_ctable(const char *title, char **rows, int nb_row, char **cols, int nb_col, int* vals, int element_width, color_palette_t *palette)
{
    int max_width_col = element_width;
    int width_garray = (nb_col+1)*(max_width_col+1)+1;

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
    chilon_pprint(&palette->borders, ".");
    chilon_pprint(&palette->title, title);
    for(int i = strlen(title)+1; i < width_garray-1; i++)
    {
        chilon_pprint(&palette->borders, "-");
    }
    chilon_pprint(&palette->borders, ".");
    chilon_print("\n");
    
    // Set columns names
    chilon_pprint(&palette->borders, "|");
    fillarray(label_buffer, max_width_col, " ");
    chilon_cprint(palette->borders.title_fg, palette->borders.title_fg, palette->borders.title_effect, label_buffer);
    chilon_pprint(&palette->borders, "|");
    // Set col labels
    for(int i = 0; i < nb_col; i++)
    {
        fillarray(label_buffer, max_width_col, cols[i]);
        chilon_pprint(&palette->name_col, label_buffer);
        chilon_pprint(&palette->borders, "|");
    }
    chilon_print("\n");
    chilon_pprint(&palette->borders, buffer);
    chilon_print("\n");

    for(int y = 0; y < nb_row; y++)
    {
        // print label
        chilon_pprint(&palette->borders, "|");
        color_font_t alter_font_attr = palette->name_row_uneven;
        color_font_t alter_font_data = palette->data_row_uneven;
        if(y%2 == 0)
        {
            alter_font_attr = palette->name_row_even;
            alter_font_data = palette->data_row_even;
        }

        fillarray(label_buffer, max_width_col, rows[y]);
        chilon_pprint(&alter_font_attr, label_buffer);
        chilon_pprint(&palette->borders, "|");
        // print values of cols
        for(int x = 0; x < nb_col; x++)
        {
            int v = *((vals+y*nb_col)+x);
            char temp[max_width_col];
            sprintf(temp, "%d", v);
            fillarray(label_buffer, max_width_col, temp);
            chilon_pprint(&alter_font_data, label_buffer);
            chilon_pprint(&palette->borders, "|");
        }
        chilon_print("\n");
    }

    // Set last delimiter line
    memset(buffer, 0, width_garray);
    strcat(buffer, "'");
    for(int i = 0; i < width_garray-2; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, "'");
    chilon_pprint(&palette->borders, buffer);
    chilon_print("\n");

    free(label_buffer);
    free(buffer);
}

void chilon_pprint(color_font_t *font, const char *text)
{
    chilon_cprint(font->title_bg, font->title_fg, font->title_effect, text);
}

void chilon_cprint(color_t bg, color_t fg, effect_t effect, const char *text)
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