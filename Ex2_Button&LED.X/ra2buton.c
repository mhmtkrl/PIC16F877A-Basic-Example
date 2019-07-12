/*
 * File:   ra2buton.c
 * Author: Mehmet KORAL
 *
 * Created on 23.01.2017 Monday, 13:37
 */


#include <xc.h>
#include "fuses.h"

#define _XTAL_FREQ 20000000
#define led PORTDbits.RD0
#define button PORTAbits.RA2

short counter = 0;

void main(void) {
    TRISA = 0x04;   //RA2 is set as an input pin
    ADCON1 = 0x06;  //Turn off ADC mode of PORTA
    TRISD  = 0x00;	//PORTD is set as an output port
    PORTD = 0x00;	//Clear all data on PORTD
    led = 0;		//Inital value on RD0 is low

    while(1) {
    	/*
			This loop runs like a toggle function
			If you press the button, then counter increases 
			if counter is equivalent to 1, then turn on LED
			else turn off LED
    	*/
        if(button) {
            counter++;
            while(button);
        }
        if(counter > 1) {
            counter = 0;
        }
        if(counter) {
            led = 1;
        }
        else {
            led = 0;
        }
    }
    return;
}
