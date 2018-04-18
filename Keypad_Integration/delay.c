#include "delay.h"

// Make a small delay
void delay(void) {}

// Delay milliseconds function
void delay_ms(int ms, int freq) {
    int i, j;
    for (j = 0; j < ms; j++)
        for (i = freq / 10000; i > 0; i--);   // delay 1 ms (approx)
}

// Delay microseconds function
void delay_us(int us, int freq) {
    int i, j;
    if (freq < FREQ_12_MHz){ // returns since inaccurate microsecond delay below 12 MHz
        return;
    }
    else{
        for (j = 0; j < us/10; j++) // allows the clock to count for more divisions
            for(i = freq/1000000; i > 0; i-- ); // delay 1 us (approx)
    }
}

// Set DCO frequency function
void set_DCO(int freq) {
    // change DC0 from default of 3MHz to 1.5MHz, 6MHz, 12MHz, 24MHz, or 48MHz.
    CS->KEY = CS_KEY_VAL; // unlock CS registers
    CS->CTL0 = 0; // clear register CTL0
    if(freq == FREQ_48_MHz) {
        /* Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */
        while
        ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
            PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
        while
        ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));

        /* Configure Flash wait-state to 1 for both banks 0 & 1 */
        FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL &
            ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
        FLCTL->BANK1_RDCTL  = (FLCTL->BANK0_RDCTL &
            ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

        /* Configure DCO to 48MHz, ensure MCLK uses DCO as source*/
        CS->CTL0 = CS_CTL0_DCORSEL_5; // Set DCO to 48MHz
        /* Select MCLK = DCO, no divider */
        CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
            CS_CTL1_SELM_3;
        CS->KEY = 0; // Lock CS module from unintended accesses
    }
    else {
        CS->CTL0 = freq; // set DCO
        // select clock sources
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
        CS->KEY = 0; // lock the CS registers
    }
}
