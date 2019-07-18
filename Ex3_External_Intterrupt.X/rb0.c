/*
 * File:   rb0.c
 * Author: Mehmet KORAL
 *
 * Created on 24.01.2018 Tuesday, 14:32
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 20000000

#define interrupt_flag INTCONbits.INTF					
#define bcd PORTD   						//Binary Code Display is connected to PORTD

unsigned char counter = 0;

void interrupt isr() {
    if(interrupt_flag) {						//Interrupt was triggered 
        counter++;							//Counter+=1
        interrupt_flag = 0;					//Clear interrupt flag
    }
}

void main(void) {
    INTCONbits.INTE = 1;    				//RB0/INT interrupt is activated
    OPTION_REGbits.INTEDG = 0; 				//Rissing mode interrupt 
    INTCONbits.GIE = 1;    					//Allowed to Interrupt
    TRISB = 0x01;   						//RB0/INT is input
    PORTB = 0x00;
    TRISD = 0x00;   						//PORTD is output for driving BCD 
    bcd = 0;
    
    while(1) {
        if(counter > 15) {
            counter = 0;
        }
        bcd = counter;
    }
    return;
}
