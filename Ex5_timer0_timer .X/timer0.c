/*
 * File:   timer0.c
 * Author: Mehmet KORAL
 *
 * Created on 25.01.2017 Wednesday, 16:12
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 20000000

#define interrupt_flag INTCONbits.T0IF
#define led1 PORTDbits.RD0

unsigned char i = 0;

void interrupt timer() {
    if(interrupt_flag) {
        TMR0 = 60;
        i++;
        if(i == 10) {
            led1 =~ led1;					//Toggle led
            i = 0;
        }
        interrupt_flag = 0;
    }
}

void main(void) {
    OPTION_REGbits.T0CS = 0;    			//Internal clock source->timer mode
    OPTION_REGbits.PSA = 0;     			//Prescalar values for Timer0
    OPTION_REGbits.PS0 = 1;     			//Prescalar = 1:256
    OPTION_REGbits.PS1 = 1;     			//Prescalar = 1:256
    OPTION_REGbits.PS2 = 1;     			//Prescalar = 1:256
    TMR0 = 60;								//Initial timer counter value is 60
    INTCONbits.T0IE = 1;    				//Timer0 interrupt is activated
    INTCONbits.GIE = 1;    					//Allowed all activated interrupts
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1) {
        
    }
    return;
}
