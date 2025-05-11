#ifndef TUIPRINTER_H
#define TUIPRINTER_H

#include <LC3.h>
#include <stdlib.h>

void startPrint(LC3* lc3, uint8_t flags);
void printFrame(LC3* lc3);
uint8_t getUserNext();


#endif//TUIPRINTER_H