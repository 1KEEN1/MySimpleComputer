#ifndef MYTERM_H
#define MYTERM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

enum colors
{
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  PURPLE,
  GRAY,
  WHITE,
  DEFAULT
};
void printCell (int address);
int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);

#endif // MYTERM_H