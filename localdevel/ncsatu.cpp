#include <ncurses.h>

int main()
{
  initscr();
  /* Begin */
  move(10,10);
  printw("Hellow Apit");
  refresh();
  getch();

  /* End */
  endwin();
  return 0;
}
