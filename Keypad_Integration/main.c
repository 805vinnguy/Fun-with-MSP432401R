/* p3_5.c: Matrix keypad scanning
 *
 * This program scans a 4x3 matrix keypad and returns a unique number
 * for each key pressed.
 *
 * Port 5 2-0 are connected to the columns and Port 5 7-4 are connected
 * to the rows of the keypad.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"
#include "keypad.h"
#include "LCD.h"
#include "LED.h"
#include <stdio.h>

#define DEBUG_KEY

int main(void) {
    unsigned char key;

    set_DCO(FREQ_24_MHz);
    LED_init();
    keypad_init();
    LCD_init();

    while(7) {
        key = keypad_getkey();              /* read the keypad */
        #ifdef DEBUG_KEY
            printf("key: %d\n", key);
        #endif
        LED_set(key);                       /* set LEDs according to the key code */
        LCD_write_char(KEYPAD_CHARS[key]);  /* write pressed keypad char to LCD */
        #ifdef DEBUG_KEYPAD_CHAR
            printf("char: %c\n", KEYPAD_CHARS[key]);
        #endif
    }
}
