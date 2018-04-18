#ifndef DELAY_H
#define DELAY_H

#include "msp.h"

//Define the values for frequencies 1.5 MHz to 48MHz
#define FREQ_1dot5_MHz 1500000
#define FREQ_3_MHz 3000000
#define FREQ_6_MHz 6000000
#define FREQ_12_MHz 12000000
#define FREQ_24_MHz 24000000
#define FREQ_48_MHz 48000000

//define functions for delaying and setting DCO
void delay(void);
void delay_ms(int ms, int freq);
void delay_us(int us, int freq);
void set_DCO(int freq);

#endif
