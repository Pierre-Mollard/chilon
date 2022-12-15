Chilon
======
``` C
/*
 __    ____ _     _ _             
 \ \  / ___| |__ (_) | ___  _ __  
  \ \| |   | '_ \| | |/ _ \| '_ \ 
   \ \ |___| | | | | | (_) | | | |
    \_\____|_| |_|_|_|\___/|_| |_|
*/                                               
```

Easily draw graphical array in the console with text format and colors

Uses :
------
- To print colored and noticeable test in the console
- Avoid the use of escape sequences in your main code, keep it clean
- To write bold, italic and even blinking text in the console
- Print colored graphical array to better see complex data
- Without the use of a dedicated GUI

Exemple :
``` C
#include "src/chilon.h"
#include <stdio.h>
#include <stdlib.h>

int array_size = 5;
char* array = "abcdef";

/// @brief Rainbow 'color' palette {fg, bg, effect}
color_palette_t rainbow_palette = {
    {RED, NORMAL, FBLINK},       //title
    {MAGENTA, NORMAL, BOLD},      //borders
    {YELLOW, GREEN, BOLD},       //name_col
    {BLUE, CYAN, BOLD},      //name_row_even
    {CYAN, BLUE, BOLD},       //name_row_uneven
    {WHITE, RED, ITALIC},    //data_row_even
    {RED, WHITE, ITALIC}      //data_row_uneven
};

int main(int argc, char* arv[])
{
    chilon_cprint(YELLOW, RED, BOLD, "this text should be bold red on yellow");
    printf("\nthis on should be normal \n");

    char *rows[8] = {"attr1", "attr2", "attr3", "attr4", "attr5", "attr6", "attr7", "attr8"};
    char *cols[5] = {"CASE 1", "CASE 2", "CASE 3", "CASE 4", "CASE 5"};
    int values[8][5] = {{0, 1, 2, 3, 4}, {10, 11, 12, 13, 14}, {20, 21, 22, 23, 24}, {30, 31, 32, 33, 34}, {40, 41, 42, 43, 44}, {50, 51, 52, 53, 54}, {60, 61, 62, 63, 64}, {70, 71, 72, 73, 74}};
    chilon_draw_table("Test Graphical Array", rows, 8, cols, 5, (int*)values, 6);
    chilon_draw_ctable("Test Graphical Array", rows, 8, cols, 5, (int*)values, 6, &rainbow_palette);
}
```

output : 

![image](https://user-images.githubusercontent.com/58636597/207298585-d84d04a7-813c-405e-b04c-9afd4871672a.png)

How to build :
--------------

A makefile is premade to help you compile the test scenario and the standalone static library.
``` bash
make # Build the test target (run) and the lib (libchilon.a)
make clean # Clean the objects file
```

Remove the executable and the library :
``` bash
make clean-lib
```

How to use
----------

Available colors (in text color (foreground) or background) :
- BLACK
- RED
- GREEN
- YELLOW
- BLUE
- MAGENTA
- CYAN
- WHITE

Available effects :
- NORMAL
- BOLD
- DIM
- ITALIC
- UNDERLINE
- SLOW BLINK
- FAST BLINK
- HIGHLIGHT
- INVISIBLE (password type)
- CROSSED

Note : some effect / colors may not be availabe on every console type, 
see [Wikipedia article about ANSI espace colors code](http://en.wikipedia.org/wiki/ANSI_escape_code#Colors) for more details
see [Wikipedia article about SGR code](https://en.wikipedia.org/wiki/ANSI_escape_code#SGR) for more details

chilon provides : 
- cprint : print with color / effects
- cprintf : formatted version of cprint
- cprint2 / cprintf2 : use struct to reduce arg number
- cfprintf / cfprintf2 : print into a specified stream
- draw_ctable : print graphical 2D array with color / effects
- draw_ccol : print 1D array vertically
- draw_crow : print 1D array horizontally 
- cursor access for better control
  
todo :
- Add color gradient/change from value
- Add catching exceptions
- Fix print with cursor
