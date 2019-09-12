//// General stuffs ////
initscr(); // "start curses"
endwin() ; // "end curses"

//// Windowing ////
WINDOW* window = newwin(height, width, startY, startX)

//// Draw ///
refresh()
wrefresh(window)

/**
 * Most functions have up to 4 variant
 * function, mvfunction, wfunction, mvwfunction
 *
 * function applies the function to the current cursor position in "stdscr"
 * mvfunction moves the cursor the given position in "stdscr"
 * wfunction applies the function to the current cursor position in the given window.
 * mvw just do both
 */

/// addch - add a character
addch(char)
mvaddch(int y,int x,char)
waddch(WINDOW*, char)
mvwaddch(WINDOW*, int y, int x, char)
/// printw - print word (mv, w, mvw)
printw(char*)
/// hline - draw a horizontal line (mv, w, mvw)
hline(char, length)
/// vline - draw a vertical line (mv, w, mvw)
wline(char, length)
/// attron / attroff - attribute on / off (w)
attron(int)
attroff(int)

///// Attribute list ////////
A_NORMAL        Normal display (no highlight)
A_STANDOUT      Best highlighting mode of the terminal.
A_UNDERLINE     Underlining
A_REVERSE       Reverse video
A_BLINK         Blinking
A_DIM           Half bright
A_BOLD          Extra bright or bold
A_PROTECT       Protected mode
A_INVIS         Invisible or blank mode
A_ALTCHARSET    Alternate character set
A_CHARTEXT      Bit-mask to extract a character
COLOR_PAIR(n)   Color-pair number n
