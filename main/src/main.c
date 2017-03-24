/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/mainHeader.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int writeUsed; 
extern int writeValue;
extern int bigChars[];
extern int SCANPRINTRADIX;

int main(int argc, char** argv)
{
  sc_memoryInit();
  sc_regInit();

  int cursorX = 0;
  int cursorY = 0;
  int position = 0;
  int fd = 0;
  int cn;
  int tmp = 0;
  int exit = 0;
  int refreshFlg = 0;
  int regis = 0;

  enum keys key;
  
  sc_regSet(FLAG_INTERRUPT, 1);

  if ((fd = open("ascibig", O_RDONLY)) == -1) {
    writeChar(2,"Cannot open ascibig\n");
    return -1;
  }

  bc_bigcharread(fd, bigChars, 17, &cn);
  close(fd);
  setSignals();
  mt_clrscr();

  /* test memory set */
  sc_commandEncode(0x10, 50, &tmp);
  sc_memorySet(0, tmp);
  sc_commandEncode(0x10, 51, &tmp);
  sc_memorySet(1, tmp);

  sc_commandEncode(0x11, 50, &tmp);
  sc_memorySet(2, tmp);
  sc_commandEncode(0x11, 51, &tmp);
  sc_memorySet(3, tmp);
  sc_commandEncode(0x40, 10, &tmp);
  sc_memorySet(4, tmp);
  sc_commandEncode(0x73, 16, &tmp);
  sc_memorySet(10, tmp);
  sc_commandEncode(0x43, 0, &tmp);
  sc_memorySet(11, tmp);

  sc_memorySet(16, 222 | (1 << 14));
  sc_memorySet(22, 23 | (1 << 14));

  accumulator = 22;

  refreshGuiSt(position);
  while (!exit) {
    if (!refreshFlg)
      refreshGui(position);

    rk_readkey(&key);
      sc_regGet(FLAG_INTERRUPT, &regis);

    if(regis) {
      switch (key) {
        case KEY_up:
          if (cursorY != 0)
            cursorY--;
          else
            cursorY = 9;

          refreshFlg = 0;
        break;

        case KEY_down:
          cursorY = (cursorY + 1) % 10;
          refreshFlg = 0;
        break;

        case KEY_left:
          if (cursorX != 0)
            cursorX--;
          else
            cursorX = 9;

          refreshFlg = 0;
        break;

        case KEY_right:
          cursorX = (cursorX + 1) % 10;
          refreshFlg = 0;
        break;

        case KEY_f5:
          refreshFlg = changeAccumulator(position);
        break;

        case KEY_f6:
          refreshFlg = changeInstRegisterCount(position);
        break;

	    case KEY_x:
          SCANPRINTRADIX = 16;
          refreshFlg = 0;
        break; 

        case KEY_d:
          SCANPRINTRADIX = 10;
          refreshFlg = 0;
        break;

        case KEY_enter:
            refreshFlg = changeCell(position);
       //   if (SCANPRINTRADIX == 10) {
       //     tmp = SCANPRINTRADIX;
      //      SCANPRINTRADIX = 16;
      //      refreshFlg = changeCell(position);
       //     SCANPRINTRADIX = tmp;
      //    } else if (SCANPRINTRADIX == 16) {
       //     refreshFlg = changeCell(position);
        //  }
        break;
					
        case KEY_t:
          timerHand(SIGALRM);
		  position = instructionRegisterCount;
          cursorX = instructionRegisterCount / 10;
          cursorY = instructionRegisterCount % 10;
        break;

        case KEY_s:
          memorySave(position);
          refreshFlg = 1;
        break;

        case KEY_l:
          memoryLoad(position);
          refreshFlg = 1;
        break;
      }
    }
    if (key == KEY_q) {
      exit = 1;
      break;
    } else if (key == KEY_i) {
      raise(SIGUSR1);
      refreshFlg = 0;
      instructionRegisterCount = 0;
      cursorX = 0;
      cursorY = 0;
    } else if (key == KEY_r) {
      sc_regGet(FLAG_INTERRUPT, &regis);
      if (regis) {
        sc_regSet(FLAG_INTERRUPT, 0);
        position = instructionRegisterCount;
        timerHand(SIGALRM);
        cursorX = instructionRegisterCount / 10;
        cursorY = instructionRegisterCount % 10;
        refreshFlg = 0;
      } else {
        alarm(0);
        sc_regSet(FLAG_INTERRUPT, 1);
        position = instructionRegisterCount;
        cursorX = instructionRegisterCount / 10 - 1;
        cursorY = instructionRegisterCount % 10;
        refreshFlg = 0;
	  }
    }
    position = cursorY + cursorX * 10;
  }
}
