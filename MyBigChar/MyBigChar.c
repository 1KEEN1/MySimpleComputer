#include "MyBigChar.h"
#include "../MySimpleComputer/MySimpleComputer.h"
#include "../MyTerm/MyTerm.h"

static int term_fd = 1;
int display_acces;

unsigned int *BigMas;

void
printCell (int address)
{

  int row, col, command, operand;
  short value;
  char buf[6];
  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return;

  row = address / 10;
  col = address % 10;

  snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);

  mt_gotoXY (2 + row, 2 + col * 6);
  write (1, buf, 5);
  write (1, "\e[m", 3);
}

void
print_memory ()
{
  bc_box (1, 1, 11, 62);
  mt_gotoXY (0, 30);
  write (1, "memory", strlen ("memory"));
  for (int i = 0; i < 100; i++)
    {
      printCell (i);
    }
}

void
print_accum ()
{
  bc_box (1, 63, 2, 90);
  mt_gotoXY (1, 70);
  write (1, "accumulator", strlen ("accumulator"));
  mt_gotoXY (2, 73);
  char *str_accum = malloc (20);
  sprintf (str_accum, "+%04x", 0x0);
  write (1, str_accum, strlen (str_accum));
}
void
print_instructionCounter ()
{
  bc_box (4, 63, 5, 90);
  mt_gotoXY (4, 67);
  write (1, "instructionCounter", strlen ("instructionCounter"));
  mt_gotoXY (5, 73);
  char *instrCounter = malloc (20);
  sprintf (instrCounter, "+%04x", 0x0);
  write (1, instrCounter, strlen (instrCounter));
}

void
print_operation ()
{
  short value;
  int mem_ptr = 2;
  int command, operand;
  bc_box (7, 63, 8, 90);
  mt_gotoXY (7, 71);
  write (1, "operation", strlen ("operation"));
  mt_gotoXY (8, 71);

  sc_memoryGet (mem_ptr, &value);
  command = value >> 7;
  operand = value & 127;
  char *operation = malloc (20);
  sprintf (operation, "+%02x : %02x", command, operand);
  write (1, operation, strlen (operation));
}

void
flags ()
{
  short value;
  bc_box (10, 63, 11, 90);
  mt_gotoXY (10, 72);
  write (1, "Flags", strlen ("Flags"));
  mt_gotoXY (11, 73);
  char flags[] = "POMTE";
  for (int i = 1; i < 6; i++)
    {
      sc_regGet (i, &value);
      if (value)
        {
          // mt_setbgcolor (RED);
          write (1, &flags[i - 1], 1);
          // mt_setbgcolor (BLACK);
        }
      else
        {
          write (1, &flags[i - 1], 1);
        }
    }
}
void
print_keys ()
{
  bc_box (13, 47, 21, 90);
  mt_gotoXY (13, 49);
  write (1, "Keys:", strlen ("Keys:"));
  mt_gotoXY (14, 48);
  write (1, "l  - load", strlen ("l  - load"));
  mt_gotoXY (15, 48);
  write (1, "s  - save", strlen ("s  - save"));
  mt_gotoXY (16, 48);
  write (1, "r  - run", strlen ("r  - run"));
  mt_gotoXY (17, 48);
  write (1, "t  - step", strlen ("t  - step"));
  mt_gotoXY (18, 48);
  write (1, "i  - reset", strlen ("i  - reset"));
  mt_gotoXY (19, 48);
  write (1, "F5  - accumulator", strlen ("F5  - accumulator"));
  mt_gotoXY (20, 48);
  write (1, "F6  - instructionCounter", strlen ("F6  - instructionCounter"));
}

void
IN_OUT ()
{
  mt_gotoXY (24, 0);
  write (1, "Input\\Output: ", strlen ("Input\\Output"));
}

void
init_bigchar ()
{
  int count = 0;
  int fd = open ("bigchar", O_RDONLY);
  BigMas = malloc (18 * 2 * sizeof (int));
  bc_bigcharread (fd, BigMas, 18, &count);
}

void
init_bigchardown ()
{
  int count = 0;
  int fd2 = open ("bigcharDown", O_RDONLY);
  BigMas = malloc (18 * 2 * sizeof (int));
  bc_bigcharread (fd2, BigMas, 18, &count);
}
void
PRNT_BC (int address)
{
  bc_box (13, 1, 21, 46);
  mt_gotoXY (14, 2);
  short value;
  char ss[8];
  int command, operand;
  sc_memoryGet (address, &value);
  sc_commandDecode (value & 0x3FFF, &command, &operand);

  snprintf (ss, 8, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);
  if (ss[0] == '-')
    {
      bc_printbigchar (BigMas, 14, 2, DEFAULT, WHITE);
    }
  else
    {
      bc_printbigchar (BigMas + 2, 14, 2, DEFAULT, WHITE);
    }

  for (int i = 0; i < 5; i++)
    {
      switch (ss[i + 1])
        {
        case '0':
          {
            bc_printbigchar (BigMas + 4, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '1':
          {
            bc_printbigchar (BigMas + 6, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '2':
          {
            bc_printbigchar (BigMas + 8, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '3':
          {
            bc_printbigchar (BigMas + 10, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '4':
          {
            bc_printbigchar (BigMas + 12, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '5':
          {
            bc_printbigchar (BigMas + 14, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '6':
          {
            bc_printbigchar (BigMas + 16, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '7':
          {
            bc_printbigchar (BigMas + 18, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '8':
          {
            bc_printbigchar (BigMas + 20, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case '9':
          {
            bc_printbigchar (BigMas + 22, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'A':
          {
            bc_printbigchar (BigMas + 24, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'B':
          {
            bc_printbigchar (BigMas + 26, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'C':
          {
            bc_printbigchar (BigMas + 28, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'D':
          {
            bc_printbigchar (BigMas + 30, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'E':
          {
            bc_printbigchar (BigMas + 32, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        case 'F':
          {
            bc_printbigchar (BigMas + 34, 14, (11 + i * 9), DEFAULT, BLUE);
            break;
          }
        }
    }
}

int
bc_printA (char *str)
{
  char *buf = malloc (20);
  sprintf (buf, "\e(0%s\e(B", str);
  write (term_fd, buf, strlen (buf));
  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2)
{
  int exit_falg = EXIT_SUCCESS;
  mt_gotoXY (x1, y1);
  for (int i = 0; i < y2 - y1; i++)
    {
      if (i == 0)
        {
          bc_printA ("l");
        }
      else
        {
          bc_printA ("q");
        }
    }
  bc_printA ("k");

  for (int i = 0; i < x2 - x1; i++)
    {
      mt_gotoXY (x1 + i + 1, y1);
      bc_printA ("x");
      mt_gotoXY (x1 + i + 1, y2);
      bc_printA ("x");
    }

  mt_gotoXY (x2 + 1, y1);

  bc_printA ("m");
  for (int i = 0; i < y2 - y1 - 1; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("j");

  mt_gotoXY (y2, 0);

  return exit_falg;
}

int
bc_printbigchar (unsigned int arr[2], int x, int y, enum colors color,
                 enum colors color_back)
{
  for (int j = 7; j >= 0; j--)
    {
      mt_gotoXY (x++, y);
      for (int i = 7; i >= 0; i--)
        {
          int value;
          bc_getbigcharpos (arr, i, j, &value);
          if (value)
            {
              mt_setbgcolor (color);
              mt_setfgcolor (color_back);
              bc_printA ("a");
            }
          else
            {
              bc_printA (" ");
            }
          mt_setbgcolor (DEFAULT);
        }
    }

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{

  if (value == 1)
    {
      big[y / 5] |= 1 << ((y - 1) * 8 + x - 1);
      return EXIT_SUCCESS;
    }
  else if (value == 0)
    {
      big[y / 5] &= ~(1 << ((y - 1) * 8 + x - 1));
      return EXIT_SUCCESS;
    }

  return EXIT_FAILURE;
}

int
bc_getbigcharpos (unsigned int *big, int x, int y, int *value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;

  int num = (y / 4) ? big[1] : big[0];
  *value = (num >> ((4 - y % 4) * 8 - x - 1)) & 1;

  return 0;
}

int
bc_bigcharwrite (int fd, unsigned int *big, int count)
{
  return write (fd, big, count * 2 * sizeof (int));
}

int
bc_bigcharread (int fd, unsigned int *big, int need_count, int *count)
{
  if ((*count = read (fd, big, need_count * 2 * sizeof (int))))
    return -1;
  *count /= sizeof (int) * 2;
  return 0;
}

void
console ()
{
  mt_clrscr ();

  init_bigchar ();
  init_bigchardown ();
  print_memory ();
  PRNT_BC (2);
  print_accum ();
  print_instructionCounter ();
  print_operation ();
  print_keys ();
  IN_OUT ();
  flags ();

  mt_setbgcolor (DEFAULT);
}