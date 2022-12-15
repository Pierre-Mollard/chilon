#include "chilon.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

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
    
    if(strlen(value) < maxwidth)
    {
        strncpy(buffer, value, maxwidth);
        char *empty_space = " ";
        for(int j = strlen(buffer); j < maxwidth; j++)
        {
            strncat(buffer, empty_space, sizeof(char));
        }
        strncat(buffer, "\0", sizeof(char));
    }else{
        strncpy(buffer, value, maxwidth);
        strncat(buffer, "\0", sizeof(char));
    }
    return buffer;
}

static void save_cursor_pos()
{
    chilon_print("\e[s");
}

static void restore_cursor_pos()
{
    chilon_print("\e[u");
}

void chilon_logo()
{
    printf(
    COLOR_FG_BLUE EFFECT_BOLD" __   "COLOR_FG_CYAN EFFECT_BOLD" ____ "COLOR_FG_BLUE EFFECT_BOLD"_     "COLOR_FG_CYAN EFFECT_BOLD"_ "COLOR_FG_BLUE EFFECT_BOLD"_             \n"COLOR_NORMAL
    COLOR_FG_BLUE EFFECT_BOLD" \\ \\"COLOR_FG_CYAN EFFECT_BOLD"  / ___"COLOR_FG_BLUE EFFECT_BOLD"| |__ "COLOR_FG_CYAN EFFECT_BOLD"(_) "COLOR_FG_BLUE EFFECT_BOLD"|"COLOR_FG_CYAN EFFECT_BOLD" ___  "COLOR_FG_BLUE EFFECT_BOLD"_ __  \n"COLOR_NORMAL
    COLOR_FG_BLUE EFFECT_BOLD"  \\ \\"COLOR_FG_CYAN EFFECT_BOLD"| |   "COLOR_FG_BLUE EFFECT_BOLD"| '_ \\"COLOR_FG_CYAN EFFECT_BOLD"| |"COLOR_FG_BLUE EFFECT_BOLD" |"COLOR_FG_CYAN EFFECT_BOLD"/ _ \\"COLOR_FG_BLUE EFFECT_BOLD"| '_ \\ \n"COLOR_NORMAL
    COLOR_FG_BLUE EFFECT_BOLD"   \\ \\"COLOR_FG_CYAN EFFECT_BOLD" |___"COLOR_FG_BLUE EFFECT_BOLD"| | | "COLOR_FG_CYAN EFFECT_BOLD"| |"COLOR_FG_BLUE EFFECT_BOLD" |"COLOR_FG_CYAN EFFECT_BOLD" (_) "COLOR_FG_BLUE EFFECT_BOLD"| | | |\n"COLOR_NORMAL
    COLOR_FG_BLUE EFFECT_BOLD"    \\_\\"COLOR_FG_CYAN EFFECT_BOLD"____"COLOR_FG_BLUE EFFECT_BOLD"|_| |_"COLOR_FG_CYAN EFFECT_BOLD"|_|"COLOR_FG_BLUE EFFECT_BOLD"_|"COLOR_FG_CYAN EFFECT_BOLD"\\___/"COLOR_FG_BLUE EFFECT_BOLD"|_| |_|"COLOR_NORMAL EFFECT_SBLINK"  :)\n"COLOR_NORMAL
    COLOR_FG_BLUE EFFECT_BOLD"                                  \n");
}

// Internal, used to output to stream with format
// core function of the 6 others available from outside the lib
static void chilon_printstream(color_t fg, color_t bg, effect_t effect, FILE* stream, const char* format, va_list ap)
{
    char* fg_color = getcolor(fg, 0);
    char* bg_color = getcolor(bg, 1);
    char* type_effect = geteffect(effect);
    char* reset = getcolor(NORMAL, 0);

    fprintf(stream, "%s%s%s", bg_color, fg_color, type_effect);
    if(ap != NULL)
    {
        vfprintf(stream, format, ap);
    }
    else
    {
        fprintf(stream, "%s", format);
    }
    fprintf(stream, "%s", reset);

    free(reset);
    free(fg_color);
    free(bg_color);
    free(type_effect);
}

void chilon_print(const char *chararray)
{
    printf("%s", chararray);
}

void chilon_printf(const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stdout, format, arglist);
    va_end(arglist);
}

void chilon_cprint(color_t bg, color_t fg, effect_t effect, const char *text)
{
    chilon_printstream(fg, bg, effect, stdout, text, NULL);
}

void chilon_cprint2(color_font_t *font, const char *text)
{
    chilon_cprint(font->title_bg, font->title_fg, font->title_effect, text);
}

void chilon_cprintf(color_t bg, color_t fg, effect_t effect, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    chilon_printstream(fg, bg, effect, stdout, format, arglist);
    va_end(arglist);
}

void chilon_cprintf2(color_font_t* font, const char* format, ...)
{
    chilon_cprintf(font->title_bg, font->title_fg, font->title_effect, format);
}

void chilon_cfprintf(FILE* stream, color_t bg, color_t fg, effect_t effect, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    chilon_printstream(fg, bg, effect, stream, format, arglist);
    va_end(arglist);
}

void chilon_cfprintf2(FILE* stream, color_font_t* font, const char* format, ...)
{
    chilon_cfprintf(stream, font->title_bg, font->title_fg, font->title_effect, format);
}

void chilon_draw_table(const char *title, char **rows, int nb_row, char **cols, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*))
{
    chilon_draw_ctable(title, rows, nb_row, cols, nb_col, (void*)vals, element_width, iter, &default_palette);
}

void chilon_draw_ctable(const char *title, char **rows, int nb_row, char **cols, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette)
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
    chilon_cprint2(&palette->borders, ".");
    chilon_cprint2(&palette->title, title);
    for(int i = strlen(title)+1; i < width_garray-1; i++)
    {
        chilon_cprint2(&palette->borders, "-");
    }
    chilon_cprint2(&palette->borders, ".");
    chilon_print("\n");
    
    // Set columns names
    chilon_cprint2(&palette->borders, "|");
    fillarray(label_buffer, max_width_col, " ");
    chilon_cprint(palette->borders.title_fg, palette->borders.title_fg, palette->borders.title_effect, label_buffer);
    chilon_cprint2(&palette->borders, "|");
    // Set col labels
    for(int i = 0; i < nb_col; i++)
    {
        fillarray(label_buffer, max_width_col, cols[i]);
        chilon_cprint2(&palette->name_col, label_buffer);
        chilon_cprint2(&palette->borders, "|");
    }
    chilon_print("\n");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    for(int y = 0; y < nb_row; y++)
    {
        // print label
        chilon_cprint2(&palette->borders, "|");
        color_font_t alter_font_attr = palette->name_row_uneven;
        color_font_t alter_font_data = palette->data_row_uneven;
        if(y%2 == 0)
        {
            alter_font_attr = palette->name_row_even;
            alter_font_data = palette->data_row_even;
        }

        fillarray(label_buffer, max_width_col, rows[y]);
        chilon_cprint2(&alter_font_attr, label_buffer);
        chilon_cprint2(&palette->borders, "|");
        // print values of cols
        for(int x = 0; x < nb_col; x++)
        {
            char temp[max_width_col];
            iter(x, y, nb_col, max_width_col, temp, vals);
            fillarray(label_buffer, max_width_col, temp);
            chilon_cprint2(&alter_font_data, label_buffer);
            chilon_cprint2(&palette->borders, "|");
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
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    free(label_buffer);
    free(buffer);
}

void chilon_draw_ccol(const char *title, int nb_row, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette)
{
    int width_garray = element_width+2;

    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc((element_width+1)*sizeof(char));
    memset(label_buffer, 0, element_width+1);

    // Set first delimiter line
    memset(buffer, 0, width_garray);
    strcat(buffer, ".");
    for(int i = 0; i < element_width; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, ".");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    chilon_cprint2(&palette->borders, "|");
    fillarray(label_buffer, element_width, title);
    chilon_cprint2(&palette->name_col, label_buffer);
    chilon_cprint2(&palette->borders, "|");
    chilon_print("\n");

    memset(buffer, 0, width_garray);
    strcat(buffer, "|");
    for(int i = 0; i < width_garray-2; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, "|");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    for(int i = 0; i < nb_row; i++)
    {
        color_font_t alter_font_data = palette->data_row_uneven;
        if(i%2 == 0)
        {
            alter_font_data = palette->data_row_even;
        }

        memset(label_buffer, 0, width_garray);
        chilon_cprint2(&palette->borders, "|");
        char temp[element_width];
        fillarray(label_buffer, element_width, iter(i, 0, 0, element_width, temp, vals));
        chilon_cprint2(&alter_font_data, label_buffer);
        chilon_cprint2(&palette->borders, "|");
        chilon_print("\n");
    }
    memset(buffer, 0, width_garray);
    strcat(buffer, "'");
    for(int i = 0; i < width_garray-2; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, "'");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    free(label_buffer);
    free(buffer);
}

void chilon_draw_crow(const char *title, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette)
{
    int width_garray = (element_width+1)*nb_col;

    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc((element_width+1)*sizeof(char));
    memset(label_buffer, 0, element_width+1);
    memset(buffer, 0, width_garray);

    //First delimiter
    strcat(buffer, ".");
    for(int i = 0; i < width_garray-1; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, ".");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    //Title
    memset(buffer, 0, width_garray);
    chilon_cprint2(&palette->borders, "|");
    fillarray(buffer, width_garray-1, title);
    chilon_cprint2(&palette->name_col, buffer);
    chilon_cprint2(&palette->borders, "|");
    chilon_print("\n");

    //Second delimiter
    memset(buffer, 0, width_garray);
    strcat(buffer, "|");
    for(int i = 0; i < width_garray-1; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, "|");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");

    //Value
    chilon_cprint2(&palette->borders, "|");
    for(int i = 0; i < nb_col; i++)
    {
        color_font_t alter_font_data = palette->data_row_uneven;
        if(i%2 == 0)
        {
            alter_font_data = palette->data_row_even;
        }

        memset(label_buffer, 0, width_garray);
        char temp[element_width];
        fillarray(label_buffer, element_width, iter(i, 0, 0, element_width, temp, vals));
        chilon_cprint2(&alter_font_data, label_buffer);
        chilon_cprint2(&palette->borders, "|");
    }
    chilon_print("\n");

    //Last delimiter
    memset(buffer, 0, width_garray);
    strcat(buffer, "'");
    for(int i = 0; i < width_garray-1; i++)
    {
        strcat(buffer, "-");
    }
    strcat(buffer, "'");
    chilon_cprint2(&palette->borders, buffer);
    chilon_print("\n");
}