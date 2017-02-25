#ifndef CPU_H
#define CPU_H

#include "./../../simpleComputer/include/sc_register.h"
#include "./../../simpleComputer/include/sc_command.h"
#include "./../../simpleComputer/include/sc_memory.h"
#include "./../../simpleComputer/include/sc.h"
#include "./../../bc/include/bc.h"
#include "./../../consoleSC/include/term.h"
#include "./../../readKey/include/readkey.h"
#include "./../../print/include/writeInt.h"
#include "./../../hardDrive/include/hardDrive.h"
#include <signal.h>
#include <fcntl.h>

/* CPU */

void CU();
int ALU(int command, int operand);

int timerHand(int sig);
int timerUrsignalHand(int sig);

void refreshGui(int position);
void printBoxes();
void printCounter();
void printKeys(int x, int y);
void printLabels();
void printOperation(int position);
void printFlags(int x, int y);
int printMcell(int *bigchars, int pos);
void printMemory(int x, int y, int position);

void setSignals();
int changeAccumulator(int pos);
int changeInstRegisterCount(int pos);
int changeCell(int pos);
int scanNum(int *plusFlag, int *n);

#endif
