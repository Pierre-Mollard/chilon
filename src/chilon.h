/**
 * Chilon is a lib coded in C to easily print data to the terminal using
 * ASCII escape sequences (color, format, etc.)
 * Free to use
 * - Pierre Mollard
 */
#ifndef __CHILON_HEADERFILE__
#define __CHILON_HEADERFILE__

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


/// @brief Print the library logo in ASCII art
void chilon_logo();


/// @brief Print a char array to the terminal
///        Does not support format, used to check 
///        if the print function is accessible to the library
/// @param chararray a const array to print
void chilon_print(const char* chararray);


/// @brief Print a table in ASCII
///        with a specified number of rows ans columns
/// @param title string table title
/// @param rows number of rows
/// @param cols number of columns
void chilon_draw_table(const char* title, int rows, int cols);


/// @brief Print text with specified color and effect
/// @param bg background color
/// @param fg foreground color (text color)
/// @param effect font effect (underlined, bold, etc.)
/// @param text text to print
void chilon_cprint(color_t bg, color_t fg, effect_t effect, char *text);

#endif