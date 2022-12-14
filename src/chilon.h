/**
 * Chilon is a lib coded in C to easily print data to the terminal using
 * ASCII escape sequences (color, format, etc.)
 * Free to use
 * - Pierre Mollard
 */
#ifndef __CHILON_HEADERFILE__
#define __CHILON_HEADERFILE__
#include <stdio.h>

/// @brief Available colors in this library
typedef enum {
    NORMAL = -1,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
} color_t;

/// @brief Available text effects in this library
typedef enum {
    NORMAL_EFFECT,
    BOLD,
    DIM,
    ITALIC,
    UNDERLINE,
    SBLINK,
    FBLINK,
    HIGHLIGHT,
    INVISIBLE,
    CROSSED,
} effect_t;

/// @brief Set of colors and effect to fully decorate a text
typedef struct color_font_
{
    color_t title_fg;
    color_t title_bg;
    effect_t title_effect;
} color_font_t;

/// @brief Set of color to define a graph (graphical array)
typedef struct color_palette_
{
    color_font_t title;
    color_font_t borders;
    color_font_t name_col;
    color_font_t name_row_even;
    color_font_t name_row_uneven;
    color_font_t data_row_even;
    color_font_t data_row_uneven;
} color_palette_t;

/// @brief Print the library logo in ASCII art
void chilon_logo();

/// @brief Print a char array to stdout
///        Does not support format or color
/// @param chararray a const array to print
void chilon_print(const char* chararray);

/// @brief Print a char array to stdout with format
/// @param format output format
void chilon_printf(const char* format, ...);

/// @brief Print text with specified color and effect
/// @param bg background color
/// @param fg foreground color (text color)
/// @param effect font effect (underlined, bold, etc.)
/// @param text text to print
void chilon_cprint(color_t bg, color_t fg, effect_t effect, const char *text);

/// @brief Print a char array to stdout with color
/// @param font color and effect (bold, underline, etc.) to apply to output
/// @param chararray a const array to print
void chilon_cprint2(color_font_t* font, const char* chararray);

/// @brief Print a char array to stdout with color and format
/// @param bg background color
/// @param fg foreground color (text color)
/// @param effect font effect (underlined, bold, etc.)
/// @param format output format
void chilon_cprintf(color_t bg, color_t fg, effect_t effect, const char* format, ...);

/// @brief Print a char array to stdout with color and format
/// @param font color and format (bold, underline, etc.) to apply to output
/// @param format output format
void chilon_cprintf2(color_font_t* font, const char* format, ...);

/// @brief Print a char array to stream with color and format
/// @param stream output stream
/// @param bg background color
/// @param fg foreground color (text color)
/// @param effect font effect (underlined, bold, etc.)
/// @param format output format
void chilon_cfprintf(FILE* stream, color_t bg, color_t fg, effect_t effect, const char* format, ...);

/// @brief Print a char array to stream with color and format
/// @param stream output stream
/// @param font color and format (bold, underline, etc.) to apply to output
/// @param format output format
void chilon_cfprintf2(FILE* stream, color_font_t* font, const char* format, ...);

/// @brief Clear screen
/// @param mode 0: clear from cursor to end of screen
///             1: clear from cursor to begining of screen
///             2: clear all
///             3: clear all + scroll buffer
void chilon_clear_screen(unsigned int mode);

/// @brief Clear line
/// @param mode 0: clear from cursor to end of line
///             1: clear from cursor to begining of line
///             2: clear all the line
void chilon_clear_line(unsigned int mode);

/// @brief Move the cursor up if 0 up if 1 down if 2 forward if 3 back
/// @param direction 0: UP 1: DOWN
///                  2: >  3: <
/// @param amount amount to move the cursor
void chilon_move_cursor(unsigned int direction, unsigned int amount);

/// @brief Move the cursor to the begining of the line up or down
/// @param direction 0 down 1 up
/// @param amount step lines to move
void chilon_set_cursor_line(unsigned int direction, unsigned int amount);

/// @brief Set the cursor along the line
/// @param x x axis along the line
void chilon_set_cursor_column(int x);


/// @brief Scroll up or down by a number of page
/// @param direction 0: down 1: up
/// @param nb_page nb of page to scroll
void chilon_scroll(unsigned int direction, unsigned int nb_page);

/// @brief Set cursor position from top left of the screen
/// @param x position from left right
/// @param y position from top down
void chilon_set_cursor_pos(unsigned int x, unsigned int y);

/// @brief Print a table in ASCII
///        with a specified number of rows ans columns
/// @param title string table title
/// @param rows row labels
/// @param nb_row number of rows
/// @param cols column labels
/// @param nb_col number of columns
/// @param vals 2D array of values
/// @param element_width width of an element in values
/// @param iter function pointer to browse data
void chilon_draw_table(const char *title, char **rows, int nb_row, char **cols, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*));


/// @brief Print a table in ASCII
///        with a specified number of rows ans columns
///        and specified colors
/// @param title string table title
/// @param rows row labels
/// @param nb_row number of rows
/// @param cols column labels
/// @param nb_col number of columns
/// @param vals 2D array of values
/// @param element_width width of an element in values
/// @param iter function pointer to browse data
/// @param palette set of color to decorate the grapical array
void chilon_draw_ctable(const char *title, char **rows, int nb_row, char **cols, int nb_col, void* vals, int element_width, char* (*iter)(int, int, int, int, char*, void*), color_palette_t *palette);

/// @brief iterator for graphical array of INTEGERs
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
/// @param x x row position in data
/// @param y y col position in data
/// @param nb_col number of columns
/// @param size_output size of the output char*
/// @param buffer buffer pre allocated
/// @param data data to search
/// @return ref to buffer
char* chilon_iter_INT(int x, int y, int nb_col, int size_output, char * buffer, void* data);

/// @brief iterator for graphical array of SHORTs
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
char* chilon_iter_SHORT(int x, int y, int nb_col, int size_output, char * buffer, void* data);

/// @brief iterator for graphical array of LONGs
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
char* chilon_iter_LONG(int x, int y, int nb_col, int size_output, char * buffer, void* data);

/// @brief iterator for graphical array of POINTERs (void*)
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
char* chilon_iter_POINTER(int x, int y, int nb_col, int size_output, char * buffer, void* data);

/// @brief iterator for graphical array of DOUBLEs
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
char* chilon_iter_DOUBLE(int x, int y, int nb_col, int size_output, char * buffer, void* data);

/// @brief iterator for graphical array of FLOATs
///        return the char* representation of element x,y in data
///        with length of size_output in the buffer
char* chilon_iter_FLOAT(int x, int y, int nb_col, int size_output, char * buffer, void* data);

#endif