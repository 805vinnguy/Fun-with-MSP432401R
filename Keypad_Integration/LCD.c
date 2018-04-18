#include "LCD.h"

void LCD_Nybble(void) { // creates falling edge to send 4 bits to LCD
    P3->OUT |= BIT7;
    delay_us(50, CS->CTL0);
    P3->OUT &= ~BIT7;
}

void LCD_command(char cmd) { // sends instructions to LCD: clear/home/entry mode/etc...
    P3->OUT &= ~(BIT0 | BIT1 | BIT2);
    P4->OUT = 0;
    P4->OUT = (cmd & UPPER_NIBBLE);
    LCD_Nybble();
    P4->OUT = ((cmd << 4) & UPPER_NIBBLE);
    LCD_Nybble();
}

void LCD_write_char(char c) { // writes data to LCD: letter A
    P3->OUT &= ~(BIT0 | BIT2);
    P3->OUT |= BIT1;
    P4->OUT = 0;
    P4->OUT = (c & UPPER_NIBBLE);
    LCD_Nybble();
    P4->OUT = ((c << 4) & UPPER_NIBBLE);
    LCD_Nybble();
    P3->OUT &= ~(BIT0 | BIT1 | BIT2);
    delay_us(100, CS->CTL0);
}

void LCD_write_string(char *str) { // writes data to LCD: string Pumpkin
    int i;
    for(i = 0; i < strlen(str); i++) {
        LCD_write_char(str[i]);
    }
}

void LCD_init(void) {
    /* LCD pins */
    P3->SEL1 &= ~(BIT5 | BIT6 | BIT7);	// set P3.5 - P3.7 as GPIO
	P3->SEL0 &= ~(BIT5 | BIT6 | BIT7);	// set P3.5 - P3.7 as GPIO
	P3->DIR |= (BIT5 | BIT6 | BIT7);    // set P3.5 - P3.7 as output
	/* RS=P3.5, RW=P3.6, E=P3.7 */
    
	P4->SEL1 &= ~(BIT4 | BIT5 | BIT6 | BIT7);	// set P4.4 - P4.7 as GPIO
	P4->SEL0 &= ~(BIT4 | BIT5 | BIT6 | BIT7);	// set P4.4 - P4.7 as GPIO
	P4->DIR |= (BIT4 | BIT5 | BIT6 | BIT7);		// set P4.4 - P4.7 as output
	/* DB4=P4.4, DB5=P4.5, DB6=P4.6, DB7=P4.7 */

    delay_ms(50, CS->CTL0); // power requires >30ms delay
    LCD_command(0x03); // function set 1
    delay_us(50, CS->CTL0); // function set requires >39us delay
    LCD_command(0x24); // function set 2
    delay_us(50, CS->CTL0); // function set requires >39us delay
    LCD_command(0x24); // function set 4
    delay_us(50, CS->CTL0); // function set requires >39us delay
    LCD_command(0x0F); // display on/off
    delay_us(50, CS->CTL0); // display toggle requires >39us delay
    LCD_command(0x01); // display clear
    delay_us(1600, CS->CTL0); // display clear requires >1.53ms delay
    LCD_command(0x06); // entry mode set
}

void LCD_clear(void) {
    command(0x01); // clear the display:Table of Commands
    delay_us(1600, CS->CTL0); // clear requires at least 1.52ms delay
}

void LCD_home(void) {
    LCD_command(0x02); // return home:Table of Commands
    delay_us(1600, CS->CTL0); // clear requires at least 1.52ms delay
}
