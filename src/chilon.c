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
    char *temp = malloc(size);
    memset(temp, 0, size);
    if (c != NORMAL)
    {
        snprintf(temp, size, (bgtype ? "\e[4%dm" : "\e[3%dm"), (int)c);
    }
    else
    {
        snprintf(temp, size, "\e[m");
    }
    return temp;
}

/// @brief ANSI Escape code from effect ID
/// @param e Effect supported from enum
/// @return escape sequence for terminal command
char *geteffect(effect_t e)
{
    int size = sizeof(char) * 8;
    char *temp = malloc(size);
    memset(temp, 0, size);
    snprintf(temp, size, "\e[%dm", (int)e);
    return temp;
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
    }else{
        strncpy(buffer, value, maxwidth);
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

static inline void draw_border_topline(color_font_t * color, color_font_t * color_text, int width, int max_width_col, char* title)
{
    chilon_cprint2(color, ".");
    if(strlen(title) >= width-2)
    {
        char *temp = malloc(width);
        strncpy(temp, title, width-2);
        temp[width-2] = '\0';
        chilon_cprint2(color_text, temp);
        free(temp);
    }
    else
    {
        chilon_cprint2(color_text, title);
    }
    
    for(int i = strlen(title)+1; i < width-1; i++)
    {
        chilon_cprint2(color, "-");
    }
    chilon_cprint2(color, ".");
    chilon_print("\n");
}

static inline void draw_border_bottomline(color_font_t * color, int width, int max_width_col)
{
    chilon_cprint2(color, "'");
    for(int i = 0; i < width-2; i++)
    {
        chilon_cprint2(color, "-");
    }
    chilon_cprint2(color, "'");
    chilon_print("\n");
}

static inline void draw_border_middleline(color_font_t * color, int width, int max_width_col)
{
    for(int i = 0; i < width-1; i++)
    {
        if(i%(max_width_col+1) == 0)
        {
            chilon_cprint2(color, "|");
        }
        else
        {
            chilon_cprint2(color, "-");
        }
    }
    chilon_cprint2(color, "|");
    chilon_print("\n");
}

static inline void draw_separator_line()
{

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

    if(element_width <= 1)
    {
        fprintf(stderr, "error, cannot print a garray element size equal or smaller than 1 char\n");
        return;
    }

    if(nb_row <= 0 || nb_col <= 0)
    {
        fprintf(stderr, "error, cannot print a garray with less than 1 row or column\n");
        return;
    }

    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc((max_width_col+1)*sizeof(char));

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
    draw_border_topline(&palette->borders, &palette->title, width_garray, element_width, title);
    
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
    draw_border_bottomline(&palette->borders, width_garray, element_width);

    free(label_buffer);
    free(buffer);
}

void chilon_draw_ccol(const char *title, int nb_row, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette)
{
    int width_garray = element_width+2;

    if(element_width <= 1)
    {
        fprintf(stderr, "error, cannot print a garray element size equal or smaller than 1 char\n");
        return;
    }

    if(nb_row <= 0)
    {
        fprintf(stderr, "error, cannot print a garray with less than 1 row\n");
        return;
    }

    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc((element_width+1)*sizeof(char));
    memset(label_buffer, 0, element_width+1);

    // Set first delimiter line
    draw_border_topline(&palette->borders, &palette->title, width_garray, element_width, title);

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
    draw_border_bottomline(&palette->borders, width_garray, element_width);

    free(label_buffer);
    free(buffer);
}

void chilon_draw_crow(const char *title, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette)
{
    int width_garray = (element_width+1)*nb_col+1;

    if(element_width <= 1)
    {
        fprintf(stderr, "error, cannot print a garray element size equal or smaller than 1 char\n");
        return;
    }

    if(nb_col <= 0)
    {
        fprintf(stderr, "error, cannot print a garray with less than 1 column\n");
        return;
    }

    char* buffer = malloc((width_garray+1)*sizeof(char));
    char* label_buffer = malloc((element_width+1)*sizeof(char));
    memset(buffer, 0, width_garray+1);
    memset(label_buffer, 0, element_width+1);

    //Title
    draw_border_topline(&palette->borders, &palette->title, width_garray, element_width, title);

    //Value
    chilon_cprint2(&palette->borders, "|");
    for(int i = 0; i < nb_col; i++)
    {
        color_font_t alter_font_data = palette->data_row_uneven;
        if(i%2 == 0)
        {
            alter_font_data = palette->data_row_even;
        }

        memset(label_buffer, 0, element_width);
        char temp[element_width];
        fillarray(label_buffer, element_width, iter(i, 0, 0, element_width, temp, vals));
        chilon_cprint2(&alter_font_data, label_buffer);
        chilon_cprint2(&palette->borders, "|");
    }
    chilon_print("\n");

    //Last delimiter
    draw_border_bottomline(&palette->borders, width_garray, element_width);

    free(label_buffer);
    free(buffer);
}