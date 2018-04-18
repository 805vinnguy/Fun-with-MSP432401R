#ifndef LED_H
#define LED_H

#include "msp.h"

#define LED_BITS (BIT0 | BIT1 | BIT2)

void LED_init(void);
void LED_set(void);

#endif