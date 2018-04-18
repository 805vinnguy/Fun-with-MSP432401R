#ifndef LCD_H
#define LCD_H

#include "msp.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPPER_NIBBLE (BIT7 | BIT6 | BIT5 | BIT4)
#define LOWER_NIBBLE (BIT3 | BIT2 | BIT1 | BIT0)

/* use key obtained via keypad_getkey() to index and write that
   that indexed char to LCD */
const char KEYPAD_CHARS[12] = { '1',  '2',  '3',
                                '4',  '5',  '6',
                                '7',  '8',  '9',
                                '*',  '0',  '#' }

void LCD_Nybble(int port_num);
void LCD_command(char c);
void LCD_write_char(char c);
void LCD_write_string(char *str);
void LCD_init(void);
void LCD_clear(void);
void LCD_home(void);

#endif
