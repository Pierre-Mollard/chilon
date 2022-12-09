/**
 * Chilon is a lib coded in C to easily print data to the terminal using
 * ASCII escape sequences (color, format, etc.)
 * Free to use
 * - Pierre Mollard
 */
#ifndef __CHILON_HEADERFILE__
#define __CHILON_HEADERFILE__

/// @brief Print a char array to the terminal
///        Does not support format, used to check 
///        if the print function is accessible to the library
/// @param chararray a const array to print
void chilon_print(const char* chararray);

#endif