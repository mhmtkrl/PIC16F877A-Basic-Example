/*
 * File:   newmain.c
 * Author: Mehmet KORAL
 *
 * Created on 21.01.2017 Saturday, 16:34
 */

#include <xc.h>
#include "fuses.h"                  //Settings of Fuse

#define _XTAL_FREQ 20000000
#define led PORTDbits.RD0           //RD0 is an output pin that we'will use for blinking to led 

void main(void) {
    TRISD = 0x00;                   //PORTD is set as an output
    PORTD = 0x00;                   //Clear data on PORTD
    
    while(1) {
        led = 1;                    //RD0 is high
        __delay_ms(100);
        led = 0;                    //RD0 is low
        __delay_ms(100);
    }
    return;
}
