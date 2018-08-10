/*
Filename: ncurseskeleton.c
Author : myapit
E-mail : 9w2xhr@gmail.com
Purpose: Basic skeleton of Ncurse code in C
Compiling : g++ -o ncurseskeleton ncurseskeleton.c -lncurses
Runnning : ./ncurseskeleton
*/

#include <ncurses.h>

int main()
{
    initscr();    /* Start curses mode  */
    printw("Hi"); /* Print Hi           */
    refresh();    /* Print it on to the real screen */
    getch();      /* Wait for user input */
    endwin();     /* End curses mode     */

    return 0;
}

/* Code Source : https://www.tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/ */
