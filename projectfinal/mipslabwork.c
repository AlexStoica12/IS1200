/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file modified 2017-04-31 by Ture Teknolog 
   Edited  2020-03-05 by L Filippeschi 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h>

#define ACC_SENSOR_ADDR 0xd0
#define ACC_SENSOR_REG  0x3b
#define EEP_SENSOR_ADDR  0xa0

int mytime = 0x5957;
int x=0;
int y=0;
int timeoutcount=0;
int timeoutcount1=0;
int pagecount=0;
int prime = 1234567;
int interrupt=0;
volatile int varx =0;
volatile int vary =0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  //timer 3 cursor interrupt handler
  if(IFS(0) & 0x1000){
    
    timeoutcount1++;
    if(life==0){
      IFS(0) |= ~0xefffff; //game over
    }
    if((timeoutcount1%2)==0){
      move_cursor(); //buttons movement
      move_cursorAcc(); //acc movement
      print_cursor(xPos, yPos, cursor);
      display_fimage(display);
      clear_cursor();
    }
    IFS(0) &= 0xefff;
  }

  //timer 2 display interrupt handler
  if(IFS(0) & 0x100){
    timeoutcount++;
    if ((timeoutcount%(12-score/7))==0){ //define speed on movement
      move_left();
      if ((pagecount%20)==0)
	spawn(randint(3),randint(2),0);
      display_fimage(display);
    }
     IFS(0) &= 0xeff;
  }

  //timer 4 software interrupt bomb explosion handler
  if(IFS(0) & 0x10000){
    int i;
    display_clear();
    
    for(i=0; i<8; i++){
      display[/*y pos*/2*136 + /*x pos*/ 62 + i]=bomb[i];
    }
    display_fimage(display);
    quicksleep(1000000);
    display_clear();
    quicksleep(1000000);
    for(i=0; i<8; i++){
      display[/*y pos*/2*136 + /*x pos*/ 62 + i]=bomb[i];
    }
    display_fimage(display);
    quicksleep(1000000);
    display_clear();
    quicksleep(1000000);
    for(i=0; i<8; i++){
      display[/*y pos*/2*136 + /*x pos*/ 62 + i]=bomb[i];
    }
    display_fimage(display);
    update_life();
    display_clear();
    IFS(0) &= 0xeffff;
  }
  
  //switch 4 interrupt handler
  if(IFS(0) & 0x080){ 
    interrupt++;
    PORTE = PORTE + 1;
    IFS(0) &= 0xf7f;
    quicksleep(100000);
  }

  //timer 5 interrupt game over;
  if(IFS(0) & 0x100000){
    display_clear();
    display_string(0, "");
    display_string(1, "      GAME");
    display_string(2, "      OVER");
    display_string(3, "");
    display_update();
    while(1){
    }
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{  
  volatile int* p = (int*) 0xbf886100;
  TRISD |= 0xfe0; 
  *p = ~0xff;
  //TRISE &= ~0xff; //set output on bits 0-7 of PORTE
   
  IPC(1) |= 0x1d0000; //sets priority max for INT1
  IEC(0) |= 0x080;  //interrupt enable on INT1
   
  //timer 2 display 
  T2CON |= 0x70; // scaler to 1:256
  T2CON |= 0x8000; //timer on
  PR2 = 2500; //period
  IPC(2) |=0x1d;    // sets priority max for timer 2
  IEC(0) |= 0x100;   // interrupt enable on timer 2
   
  //timer 3 cursor
  T3CON |= 0x70;
  T3CON |= 0x8000;
  PR3 = 2400; //period
  IPC(3) |=0x1d;    // sets priority max for timer 3
  IEC(0) |= 0x1000;   // interrupt enable on timer 3

  //timer 4 used as software interrupt bomb animation
  IPC(4) |=0x1e;    // sets priority max for timer 4
  IEC(0) |= 0x10000;   // interrupt enable on timer 4

  //timer 4 used as software interrupt game over 
  IPC(5) |=0x1f;    // sets priority max for timer 4
  IEC(0) |= 0x100000;   // interrupt enable on timer 4

  int i,j; 
  for(i=0; i<24; i++)
    for(j=0; j<136; j++)
      support[i][j]=0;

  enable_interrupt();
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  //at every loop updates the values from the accelerometer to get accurate data
  i2c_start();
  i2c_send(ACC_SENSOR_ADDR);
  i2c_send(ACC_SENSOR_REG);

  i2c_start();
  i2c_send(ACC_SENSOR_ADDR + 1);
  varx = i2c_recv() << 8;
  i2c_ack();
  varx |= i2c_recv();
  i2c_ack();
  vary = i2c_recv() << 8;
  i2c_ack();
  vary |= i2c_recv();
  i2c_nack();
  i2c_stop();
  
  xAcc=totwos(varx);
  yAcc=totwos(vary);
}
