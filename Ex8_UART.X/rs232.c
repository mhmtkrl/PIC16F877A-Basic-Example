/*
 * File:   rs232.c
 * Author: Mehmet KORAL
 *
 * Created on 05.02.2017 Sunday, 14:45
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "fuses.h"
#include "rs.h"
#include <math.h>

int i = 0;
float sinValue = 0;
char s[20];


void main(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    
    UART_config(9600, 1);
    
    while(1) {
        i+=1;
        if(i >= 1000) {
            i = 0;
        }
        sinValue = sin(6*i);
        
        __delay_ms(100);
        
        sprintf(s, "Sin= %f\r\n", sinValue);
        send_string(s);
    }
    return;
}
