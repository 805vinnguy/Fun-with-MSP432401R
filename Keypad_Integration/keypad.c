#include "keypad.h"

/* this function initializes Port 5 that is connected to the keypad.
 * All pins are configured as GPIO input pin. The column pins have
 * the pull-up resistors enabled.
 */
void keypad_init(void) {
    P5->SEL1 = 0;       /* using all pins so set all port 5 pins to GPIO */
    P5->SEL0 = 0;
    P5->DIR = 0;
    P5->REN |= 0x07;     /* enable pull resistor for column pins */
    P5->OUT |= 0x07;     /* make column pins pull-ups */
    /* C=P5.0, A=P5.1, E=P5.2, B=P5.4, G=P5.5, F=P5.6, D=P5.7 */
}

/*
 * This is a non-blocking function to read the keypad.
 * If a key is pressed, it returns a unique code for the key. Otherwise,
 * a zero is returned.
 * The lower nibble of Port 5 is used as input and connected to the columns.
 * Pull-up resistors are enabled so when the keys are not pressed, these pins
 * are pulled high.
 * The upper nibble of Port 5 is used as output that drives the keypad rows.
 * First all rows are driven low and the input pins are read. If no key is pressed,
 * they will read as all one because of the pull up resistors. If they are not
 * all one, some key is pressed.
 * If some key is pressed, the program proceeds to drive one row low at a time and
 * leave the rest of the rows inactive (float) then read the input pins.
 * Knowing which row is active and which column is active, the program
 * can decide which key is pressed.
 *
 * Only one row is driven so that if multiple keys are pressed and row pins are shorted,
 * the microcontroller will not be damaged. When the row is being deactivated,
 * it is driven high first otherwise the stray capacitance may keep the inactive
 * row low for some time.)
 */
char keypad_getkey(void) {
    int row, col;
    const char row_select[] = {B, G, F, D}; /* one row is active */

    /* check to see any key pressed */
    P5->DIR |= (B | G | F | D);         /* make all row pins output */
    P5->OUT &= ~(B | G | F | D);        /* drive all row pins low */
    delay_ms(50, CS->CTL0);             /* wait for signals to settle */
    col = (P5->IN & (C | A | E));       /* read column pins  */
    P5->OUT |= (B | G | F | D);         /* drive all rows high before disable them */
    P5->DIR &= ~(B | G | F | D);        /* disable all row pins drive */
    if (col == (C | A | E))             /* if all columns are high */
        return 0;                       /* no key pressed */

    /* If a key is pressed, it gets here to find out which key.
     * It activates one row at a time and read the input to see
     * which column is active. */
    for (row = 0; row < 4; row++) {
        P5->DIR &= ~(B | G | F | D);    /* disable all rows by making them input*/
        P5->DIR |= row_select[row];     /* enable one row at a time by making it output*/
        P5->OUT &= ~row_select[row];    /* drive the active row low */
        delay_ms(50, CS->CTL0);         /* wait for signal to settle */
        col = (P5->IN & (C | A | E));   /* read columns */
        P5->OUT |= row_select[row];     /* drive the active row high */
        if (col != (C | A | E)) break;  /* if one of the input is low, some key is pressed. */
    }
    P5->OUT |= (B | G | F | D);         /* drive all rows high before disable them */
    P5->DIR &= ~(B | G | F | D);        /* disable all rows by making them input*/
    if (row == 4)
        return 0;                       /* if we get here, no key is pressed */

    /* gets here when one of the rows has key pressed, check which column it is */
    if (col == (A | E)) return row * 3 + 1;    /* key in column 0 */
    if (col == (C | E)) return row * 3 + 2;    /* key in column 1 */
    if (col == (A | C)) return row * 3 + 3;    /* key in column 2 */

    return 0;   /* just to be safe */
}
