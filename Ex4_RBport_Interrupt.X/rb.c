/*
 * File:   rb.c
 * Author: Mehmet KORAL
 *
 * Created on 24.01.2017 Tuesday, 15:08
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 20000000

#define interrupt_flag INTCONbits.RBIF  		

bit b0 = 0, b1 = 0, b2 = 0, b3 = 0;
unsigned char counter = 0;

void interrupt isr() {
    if(interrupt_flag) {
        b0 = PORTBbits.RB4;
        b1 = PORTBbits.RB5;
        b2 = PORTBbits.RB6;
        b3 = PORTBbits.RB7;
        counter++;
        interrupt_flag = 0;
    }
    
}

void main(void) {
    INTCONbits.RBIE = 1;    				//RB interrupt is activated
    INTCONbits.GIE = 1;     				//Allow all activated interrupt
    TRISB = 0xF0;   						//B[0:3] are output, B[4:7] are input
    PORTB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1) {
    	/*
			Just to see of output's state on PORTB by interrupt event,
			at the same, we can see how many interrupts have been generated so far on PORTD
    	*/
        PORTBbits.RB0 = b0;				
        PORTBbits.RB1 = b1;
        PORTBbits.RB2 = b2;
        PORTBbits.RB3 = b3;
        PORTD = counter;
    }
    return;
}
