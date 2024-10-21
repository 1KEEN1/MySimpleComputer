#include "../MyBigChar/MyBigChar.h"
#include "../MySimpleComputer/MySimpleComputer.h"
#include "../MyTerm/MyTerm.h"
#include <stdio.h>
#include <unistd.h>

int
main ()
{
  static int term_fd = 0;
  int rows = 0;
  int cols = 0;
  struct winsize ws;
  if (ioctl (term_fd, TIOCGWINSZ, &ws) < 0)
    return -1;
  rows = ws.ws_row;
  cols = ws.ws_col;

  if ((rows <= 25) || (cols <= 100))
    return printf ("Error.\n");

  mt_clrscr ();

  sc_memoryInit ();
  sc_regInit ();
  sc_memorySet (2, 15);
  console ();
  mt_gotoXY (48, 0);
  mt_setbgcolor (DEFAULT);
  return 0;
}