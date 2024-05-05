#include <stdio.h>
#include <ncurses.h>

int main() {

  listenServer();
  
  initscr();

  int height = 20, width = 20, y = 4, x = 10; 

  WINDOW* win = newwin(height, width, y, x);
  refresh();

  box(win, 0, 0);
  mvwprintw(win, 1, 1, "This is a txt");
  wrefresh(win);

  int c = getch();
  endwin();

  return 0;
}
 

/*
  initscr();

  int x = 5, y = 5;
  refresh();

  move(y, x);
    printw("Hello world from ncurses!, ");

    mvprintw(0, 0, "Hello world from ncurses!, ");
  int c = getch();

  wborder

  refresh();
  printw("%d", c);

  getch();
  endwin();
*/