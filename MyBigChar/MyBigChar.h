#include "../MyTerm/MyTerm.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

/*l = ┌
  k = ┐
  m = └
  j = ┘
  q= ─
  x= │
  a = █
*/
extern unsigned int *BigMas;
void init_bigchar ();
#define BC_SIZE_DEFAULT 2
int bc_bigcharLayout (int *bigC, char value);
int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printbigchar (unsigned int arr[2], int x, int y, enum colors color,
                     enum colors color_back);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (unsigned int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, unsigned int *big, int count);
int bc_bigcharread (int fd, unsigned int *big, int need_count, int *count);