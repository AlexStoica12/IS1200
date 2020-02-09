/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* p = 0xbf886100;
  TRISD |= 0xfe0; 
  *p = ~0xff;
  //TRISE &= ~0xff; //set output on bits 0-7 of PORTE
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* p =0xbf886110;
  int x=getbtns();
  if(x){
    int y =0;
    y= getsw();
    if(x/8){
      mytime = (mytime & 0x0fff) | y<<12;
      x-=8;
    }
    if(x/4){
      mytime = (mytime & 0xf0ff) | y<<8;
      x-=4;
    }
    if(x/2){
      mytime = (mytime & 0xff0f) | y<<4;
      x-=2;
    }
    if(x/1){
      mytime = (mytime & 0xfff0) | y;
      x-=1;
    }
  }
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *p += 1; 
  display_image(96, icon);
}
