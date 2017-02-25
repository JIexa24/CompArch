#include "./../include/mainHeader.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int bigChars[];

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

  enum keys key;
  
  sc_regSet(FLAG_INTERRUPT, 1);

  if ((fd = open("ascibig", O_RDONLY)) == -1) {
    write(2,"Cannot open ascibig\n", 20);
    return -1;
  }
  mt_clrscr();
  bc_bigcharread(fd, bigChars, 128, &cn);
  close(fd);

  sc_commandEncode(0x10, 126, &tmp);
  sc_memorySet(0, tmp);
  sc_memorySet(1, 2);
  
  while (!exit) {
    refreshGui(position);
    rk_readkey(&key);

    if(BITCHECK(FLAG_INTERRUPT, 1)) {

      switch (key) {
        case KEY_up:
          if (cursorY != 0)
            cursorY--;
          else
            cursorY = 9;
        break;

        case KEY_down:
          cursorY = (cursorY + 1) % 10;
        break;

        case KEY_left:
          if (cursorX != 0)
            cursorX--;
          else
            cursorX = 9;
        break;

        case KEY_right:
          cursorX = (cursorX + 1) % 10;
        break;

        case KEY_f5:
          changeAccumulator(position);
        break;

        case KEY_f6:

        break;
	
        case KEY_enter:
          changeCell(position);
        break;
					
        case KEY_t:
          timerHand(SIGALRM);
		  position = instructionRegisterCount;
          cursorX = instructionRegisterCount % 10;
          cursorY = instructionRegisterCount / 10;
        break;

        case KEY_s:

        break;

        case KEY_l:

        break;
      }
    }
    if (key == KEY_q)
      exit = 1;
    else if (key == KEY_i) {
      position = 0;
      cursorX = 0;
      cursorY = 0;
    }
    position = cursorY + cursorX * 10;
  }
}
