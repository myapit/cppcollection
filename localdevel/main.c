#include <ncurses.h>

int main()
{
  initscr();
  raw();
  //attron(A_STANDOUT | A_UNDERLINE);
  start_color();
  init_pair(1,COLOR_RED, COLOR_BLUE);
  attron(COLOR_PAIR(1));
  printw ("WOOOOO");
  //attroff(A_STANDOUT | A_UNDERLINE);
  attroff(COLOR_PAIR(1));

  getch();
  endwin();
  return 0;
}
