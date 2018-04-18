#include "LED.h"

/* Initialize tri-color LEDs on the LaunchPad board.
 * P2.0 - red
 * P2.1 - green
 * P2.2 - blue
 */
void LED_init(void) {
    P2->DIR = LED_BITS;         /* make LED pins output */
    P2->OUT &= ~LED_BITS;       /* turn the LEDs off */
}

/* turn on or off the LEDs according to bit 2-0 of the value */
void LED_set(int value) {
    value &= LED_BITS;          /* only bit 2-0 are affected */
    P2->OUT = (P2->OUT & ~LED_BITS) | value;
}
