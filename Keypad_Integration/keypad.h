#ifndef KEYPAD_H
#define KEYPAD_H

#include "msp.h"
#include "delay.h"

#define A BIT1
#define B BIT4
#define C BIT0
#define D BIT7
#define E BIT2
#define F BIT6
#define G BIT5

void keypad_init(void);
char keypad_getkey(void);

#endif
