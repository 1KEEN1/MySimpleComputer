#include <stdio.h>
#include <stdlib.h>

#define RAM_SIZE 100
short RAM_GLOBAL[RAM_SIZE];
extern int flag_register;
extern const int correct_ops[];
extern const int ops_num;

#define FLAG_OVERFLOW 0 // переполнение
#define FLAG_DIVISION 1 // деление
#define FLAG_OUTMEM 2   // недостаток памяти
#define FLAG_INTERUPT 3 // прерывание
#define FLAG_COMMAND 4  // команда

int sc_memoryInit ();
int sc_memorySet (int address, short value);
int sc_memoryGet (int address, short *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int register_n, short value);
int sc_regGet (int register_n, short *value);
int sc_commandEncode (int command, int operand, short *value);
int sc_commandDecode (short value, int *command, int *operand);