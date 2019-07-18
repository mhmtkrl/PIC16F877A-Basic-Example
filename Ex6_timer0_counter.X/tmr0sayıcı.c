/*
 * File:   tmr0sayýcý.c
 * Author: Mehmet KORAL
 *
 * Created on 25.01.2017 Wednesday, 16:35
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 20000000

#define interrupt_flag INTCONbits.TMR0IF
#define led PORTAbits.RA0

unsigned char i = 0;

void interrupt sinyal() {
    if(interrupt_flag) {
        TMR0 = 255;
        led =~ led;
        i++;
        interrupt_flag = 0;
    }   
}

void main(void) {
    OPTION_REGbits.T0CS = 1;    					//External clock source->Counter mode
    OPTION_REGbits.T0SE = 1;    					//Rising mode 
    OPTION_REGbits.PSA = 1;     					//Prescalar for WDT(Prescalar must be 1:1 for counting)
    /*
     * If you want timer0 to increase by one by then PSA must be 1
     */
    OPTION_REGbits.PS0 = 0;     					//Prescalar is 1:2
    OPTION_REGbits.PS1 = 0;     					//Prescalar is 1:2
    OPTION_REGbits.PS2 = 0;    						//Prescalar is 1:2
    TMR0 = 255;										//Initial value of timer0 is 255
    INTCONbits.TMR0IE = 1;   				        //Timer0's interrupt is activated			
    INTCONbits.GIE = 1;    						    //Allowed all activated interrupt
    TRISA = 0x10;   								//RA4 is input for timer0(counter mode)
    ADCON1 = 0x06;  								//PORTA is set as a Digital port
    TRISD = 0x00;
    PORTD = 0x00;
    while(1) {
        PORTD = i;
    }
    return;
}
