#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
  return (PORTD>>8)&0xf;
}

int getbtns(void){
  int rtrn=0;
  TRISF &= 0x2;
  rtrn |= (PORTD>>4)&0xe | (PORTF>>1)&0x1;
  //  TRISF |= 0x2;
  return  rtrn;
}

