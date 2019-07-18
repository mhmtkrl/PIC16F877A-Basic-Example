/*
 * File:   adcoku.c
 * Author: Mehmet KORAL
 *
 * Created on 07.02.2017 Tuesday, 16:35
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "fuses.h"
#include "rs.h"

unsigned int data[8] = 0;
char s[20];
char i = 0;

void adc_init() {
    ADCON0 = 0x81;									//Fosc/32 & A/D module is powered up
    ADCON1 = 0x80;    								//Right justified on the ADRES[H:L] register
}

unsigned int read_adc(unsigned char channel) {
    ADCON0 &= 0xC7;
    ADCON0 |= (channel << 3);						//Analog channel select
    __delay_us(20);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);						//Go_nDONE bit is automatically cleared by hardware when A/D conversation is complete 
    return ((ADRESH << 8) + ADRESL);
}

void main(void) {
    adc_init();										//ADC init function
    TRISA = 0xFF;
    TRISE = 0x07;
    TRISD = 0x00;
    PORTD = 0x00;
    UART_config(9600, 1);							//UART is activated

    sprintf(s, "ADC implemantation on PIC mcu...\r\n");
    send_string(s);
    
    while(1) {
    	/*
			Read all A/D channels
    	*/
        for(i = 0 ; i < 8 ; i++) {
            sprintf(s, "Sensor[%d] = %d\r\n", i, read_adc(i));
            send_string(s);
            __delay_ms(100);
        }
        send_string("\r\n");
        __delay_ms(500);
    }
    return;
}