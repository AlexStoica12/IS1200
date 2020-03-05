/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall
   Edited  2020 by L Filippeschi

   For copyright and licensing, see file COPYING */

/* Copyright (C) 1998-2017 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * ISO C Standard:  7.16  Boolean type and values  <stdbool.h>
 */

#ifndef _STDBOOL_H
#define _STDBOOL_H

#ifndef __cplusplus

#define bool	_Bool
#define true	1
#define false	0

#else /* __cplusplus */

/* Supporting _Bool in C++ is a GCC extension.  */
#define _Bool	bool

#if __cplusplus < 201103L
/* Defining these macros in C++98 is a GCC extension.  */
#define bool	bool
#define false	false
#define true	true
#endif

#endif /* __cplusplus */

/* Signal that all the definitions are present.  */
#define __bool_true_false_are_defined	1

#endif	/* stdbool.h */


#define ACC_SENSOR_ADDR 0xd0
#define ACC_SENSOR_REG  0x3b
#define EEP_SENSOR_ADDR 0xa0

extern int life;
extern uint8_t score;
extern int pagecount;
extern int out;
extern uint8_t leader;

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];

/* Declare bitmap array containing icon */
extern char support[24][136]; 
extern uint8_t display[136*4];
extern const uint8_t const pear[8];
extern const uint8_t const bomb[8];
extern const uint8_t const heart[8];
extern const uint8_t const banana[8];
extern const uint8_t const cursor[2];
extern const uint8_t const watermelon[8];
extern const uint8_t const icon[128];
extern const uint8_t const test[128];
extern const uint8_t const intro[136*4];
extern const uint8_t const intro1[136*4];
extern const uint8_t const bomb1[136*4];
extern const uint8_t const bomb2[136*4];
extern const uint8_t const bomb3[136*4];
extern const uint8_t const gameover1[136*4];
extern const uint8_t const gameover2[136*4];
extern const uint8_t const ninja[136*4];
extern const uint8_t const textintro[136*4];

/* Declare text buffer for display output */
extern char textbuffer[4][16];

extern volatile int xPos;
extern volatile int yPos;
extern volatile int xAcc;
extern volatile int yAcc;
extern int eepromdata;
extern uint8_t leaderboard[3];

void acc_init(void);
void i2c_idle(void);
bool i2c_send(uint8_t data);
uint8_t i2c_recv(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);

void get_acc(int* xacc, int* yacc);

void update_life(void);
void update_score(void);
void display_clear(void);
void move_left(void);
void move_right(void);
int rand(void);
int randint(int n);
void spawn(int obj, int row, int dir);
void bomb_explosion(void);
int pow(int base, int exponent);
void print_cursor (int x,int y,const uint8_t *data);
void clear_fruit(int page);
void clear_cursor(void);
void clear_eeprom(void);
void move_cursor(void);
void move_cursorAcc(void);

int totwos(int num);
char* toArray(int num);


/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
