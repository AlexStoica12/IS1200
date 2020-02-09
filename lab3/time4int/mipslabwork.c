/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file modified 2017-04-31 by Ture Teknolog 
   Edited  2020-02-09 by L Filippeschi 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int timeoutcount=0;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  IFS(0) &= 0xeff;
  timeoutcount++;
  if ((timeoutcount%10)==0){
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
    tick (&mytime);
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* p = (int*) 0xbf886100;
  TRISD |= 0xfe0; 
  *p = ~0xff;
  //TRISE &= ~0xff; //set output on bits 0-7 of PORTE
  T2CON |= 0x70; // scaler to 1:256
  T2CON |= 0x8000; //timer on
  PR2 = 31250; //period to 31250
  IPC(2) |=0x1f;    // sets priority max for timer 2
  IEC(0) |= 0x100;   // interrupt enable on timer 2
  enable_interrupt();
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update;
}
