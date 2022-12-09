/**
 * Chilon is a lib coded in C to easily print data to the terminal using
 * ASCII escape sequences (color, format, etc.)
 * Free to use
 * - Pierre Mollard
 */
#ifndef __CHILON_HEADERFILE__
#define __CHILON_HEADERFILE__


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

#endif