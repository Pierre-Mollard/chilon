'''chilon.py
-   dependencies : requests bs4
-
'''
from ctypes import *
import pathlib
from enum import Enum

LIBRARY_C_SHARED_OBJECT_PATH = '../bin/libchilon.so'
path = pathlib.Path(__file__).parent.resolve()

# enum
Color = {'NORMAL':-1, 
    'BLACK':0,
    'RED':1,
    'GREEN':2,
    'YELLOW':3,
    'BLUE':4,
    'MAGENTA':5,
    'CYAN':6,
    'WHITE':7}

Effect = { 
    'NORMAL_EFFECT':0,
    'BOLD':1,
    'DIM':2,
    'ITALIC':3,
    'UNDERLINE':4,
    'SBLINK':5,
    'FBLINK':6,
    'HIGHLIGHT':7,
    'INVISIBLE':8,
    'CROSSED':9}

# structures
class FONT(Structure):
    _fields_ = [('title_fg', c_int),
                ('title_bg', c_int),
                ('title_effect', c_int)]

class PALETTE(Structure):
    _fields_ = [('title', FONT),
                ('borders', FONT),
                ('name_col', FONT),
                ('name_row_even', FONT),
                ('name_row_uneven', FONT),
                ('data_row_even', FONT),
                ('data_row_uneven', FONT)]

libC = CDLL(str(path) + '/' + LIBRARY_C_SHARED_OBJECT_PATH)

# Print the library logo in ASCII art
def logo():
    libC.chilon_logo()

# Print a char array
def print(text):
    libC.chilon_print(text.encode())

# Print a char array with format, encode your string!
def printf(*args):
    libC.chilon_printf(*args)

# Print text with specified color and effect
def cprint(bg, fg, effect, text):
    libC.chilon_cprint(bg, fg, effect, text.encode())

# Print a char array with color using font class
def cprint2(font, text):
    libC.chilon_cprint2(pointer(font), text.encode())

# Print a char array with format, encode your string!
def cprintf(bg, fg, effect, *args):
    libC.chilon_cprintf(bg, fg, effect, *args)
    
# Print a char array with format, encode your string!
def cprintf2(font, *args):
    libC.chilon_cprintf2(pointer(font), *args)

# Clear screen
# 0: clear from cursor to end of screen
# 1: clear from cursor to begining of screen
# 2: clear all
# 3: clear all + scroll buffer
def clear_screen(mode):
    libC.chilon_clear_screen(mode)

# Clear line
def clear_line(mode):
    libC.chilon_clear_line(mode)

# Move the cursor to 0 up, 1 down, 2 forward, 3 back if inside the edge of terminal
def chilon_move_cursor(direction, amount):
    libC.chilon_move_cursor(direction, amount)

# Move the cursor to the begining of the line up or down
def set_cursor_line(direction, amount):
    libC.chilon_set_cursor_line(direction, amount)

# Set the cursor along the line
def set_cursor_column(x):
    libC.chilon_set_cursor_column(x)

# Scroll up or down by a number of page
def scroll(direction, amount):
    libC.chilon_scroll(direction, amount)

# Set cursor position from top left of the screen
def set_cursor_pos(x, y):
    libC.set_cursor_pos(x,y)

