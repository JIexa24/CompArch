#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

int timerHand(int sig)
{
  refreshGui(instructionRegisterCount);
  CU();
  instructionRegisterCount++;
  if (!BITCHECK(sc_register, FLAG_INTERRUPT)) {
    alarm(1);
  }
}
