/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_register.h"

extern int localRAM[];
extern short int sc_register;

extern int* correctCommands;


int sc_regInit(void)
{
  sc_register = 0;
  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_regSet(int scRegister, int value)
{
  if ((scRegister >= 0) && (scRegister <=5) && (value >= 0) && (value < 2)) {
    if (value == 1) {
      BITSET(sc_register, scRegister);
    } else if (value == 0) {
      BITCLEAR(sc_register, scRegister);
    } else {
	  return 0;
    }		
  }	else {
    return ERR_WRONG_FLAG;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_regGet(int scRegister, int* value)
{
  if ((scRegister >= 0) && (scRegister <=6)) {
    *value = BITCHECK(sc_register, scRegister);
    return *value;
  } else { 
    return ERR_WRONG_FLAG;
  }
  return 0;
}
