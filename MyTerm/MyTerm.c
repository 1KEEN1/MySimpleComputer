#include "MyTerm.h"
#include "../MySimpleComputer/MySimpleComputer.h"
static int term_fd = 0; // файловый дескриптор терминала

int
mt_clrscr (void)
{
  if (write (term_fd, "\e[H\e[J", 6) < 0)
    return -1;
  return 0;
}

int
mt_gotoXY (int x, int y)
{
  char buf[16];
  int len = sprintf (buf, "\e[%d;%dH", x, y);
  if (write (term_fd, buf, len) < 0)
    return -1;
  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (ioctl (term_fd, TIOCGWINSZ, &ws) < 0)
    return -1;
  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}

int
mt_setfgcolor (enum colors color)
{
  if (color < BLACK || color > WHITE)
    return -1;
  char *str = malloc (20);
  sprintf (str, "\e[3%dm", color);
  write (1, str, strlen (str));
  return 0;
}

int
mt_setbgcolor (enum colors color)
{
  if (color < BLACK || color > WHITE)
    return -1;
  char *str = malloc (20);
  sprintf (str, "\e[4%dm", color);
  write (1, str, strlen (str));
  return 0;
}