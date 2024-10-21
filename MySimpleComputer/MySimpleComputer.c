#include "MySimpleComputer.h"

const int correct_ops[] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
                            0x33, 0x40, 0x41, 0x42, 0x43, 0x59 };
const int ops_num = 13;
int flag_register;
int
sc_memoryInit ()
{
  for (int i = 0; i < RAM_SIZE; i++)
    {
      RAM_GLOBAL[i] = 0;
    }
  return EXIT_SUCCESS; // Завершение работы функции
}

int
sc_memorySet (int address, short value)
{
  if (address >= 0 && address < 100)
    {
      RAM_GLOBAL[address] = value;
    }
  else
    {
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int
sc_memoryGet (int address, short *value)
{
  if (address >= 0 && address < 100)
    {
      *value = RAM_GLOBAL[address];
    }
  else
    {
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int
sc_memorySave (char *filename)
{
  FILE *outFile;
  outFile = fopen (filename, "wb");
  fwrite (RAM_GLOBAL, sizeof (int), RAM_SIZE, outFile);
  fclose (outFile);
  return EXIT_SUCCESS;
}

int
sc_memoryLoad (char *filename)
{
  FILE *infile;
  infile = fopen (filename, "rb");
  if (infile == NULL)
    {
      return EXIT_FAILURE;
    }
  else
    {
      fread (RAM_GLOBAL, sizeof (int), RAM_SIZE, infile);
    }
  fclose (infile);
  return EXIT_SUCCESS;
}

int
sc_regInit (void)
{
  flag_register = 0;
  return EXIT_SUCCESS;
}
int
sc_regSet (int register_n, short value)
{
  if (register_n >= 0 && register_n <= 4)
    {
      if (value == 1)
        {
          flag_register = flag_register | (1 << (register_n));
        }
      else if (value == 0)
        {
          flag_register = flag_register & ~(1 << (register_n));
        }
    }
  return EXIT_SUCCESS;
}
int
sc_regGet (int register_n, short *value)
{
  if (register_n >= 0 && register_n <= 4)
    {
      *value = flag_register & ~(1 << (register_n));
    }
  return EXIT_SUCCESS;
}

int
sc_commandEncode (int command, int operand, short *value)
{
  if (command > 0x7f || operand > 0x7f)
    return -1;

  *value = (command << 7) | operand;
  return 0;
}

int
sc_commandDecode (short value, int *command, int *operand)
{
  if (value >> 14)
    {
      return -1;
    }

  *command = value >> 7;
  *operand = value & 0x7F;

  return 0;
}