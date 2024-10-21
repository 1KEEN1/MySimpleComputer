#include "MyBigChar.h"
#include <fcntl.h>
int
main ()
{
  int fd = open ("bigcharDown", O_WRONLY | O_CREAT);
  unsigned int big[36] = {
    0x000000FF, 0x0,        6168,       4279769088, 4291019715, 3284386815,
    3233857728, 3233857728, 0x7cc36030, 0x180c06ff, 0xffc0c0ff, 0xc0c0c0ff,
    0xc3c3c3ff, 0xC0C0C0C0, 0xff0303ff, 0xc0c0c0ff, 0xff0303ff, 0xc3c3c3ff,
    0xffc0c0c0, 0xc0c0c0c0, 0xffc3c3ff, 0xc3c3c3ff, 0xffc3c3ff, 0xc0c0c0ff,
    0x3cc3c3ff, 0xc3c3c3c3, 0x3fc3c33f, 0xc3c3c33f, 0x3cc30303, 0x0303c33c,
    0x3fc3c3c3, 0xc3c3c33f, 0xff0303ff, 0x030303ff, 0xff0303ff, 0x03030303
  };
  bc_bigcharwrite (fd, big, 18);
}

// FFC0 C0C0 c0c0c0ff
// FFC0 C0FF ffc0c0ff