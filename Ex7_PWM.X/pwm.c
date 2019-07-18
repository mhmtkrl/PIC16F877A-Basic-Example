/*
 * File:   pwm.c
 * Author: Mehmet KORAL
 *
 * Created on 04.02.2017 Saturday, 16:50
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 20000000
#define T2prescaler 4

signed short i = 0;
long frequency = 0;

int max_pwm_duty() {
    return(_XTAL_FREQ / (frequency * T2prescaler));
}

pwm1_Init(long fre) {
    PR2 = (_XTAL_FREQ / (fre * 4 * T2prescaler)) - 1;
    frequency = fre;
}

pwm1_duty(unsigned int duty) {
    if(duty < 1024) {
        duty = ((float)duty / 1023) * max_pwm_duty();
        CCP1CONbits.CCP1X = duty & 2;
        CCP1CONbits.CCP1Y = duty & 1;
        CCPR1L = duty >> 2;
    }
}

void main(void) {
    T2CONbits.T2CKPS0 = 1;  				//Prescalar is 1:4
    T2CONbits.T2CKPS1 = 0;  				//Prescalar is 1:4
    T2CONbits.TMR2ON = 1;   				//Timer2 is activated
    T2CONbits.TOUTPS0 = 0;
    T2CONbits.TOUTPS1 = 0;
    T2CONbits.TOUTPS2 = 0;
    T2CONbits.TOUTPS3 = 0;  				//Postscale is 1:1
    
    CCP1CONbits.CCP1M0 = 1;					//PWM mode
    CCP1CONbits.CCP1M1 = 1;
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M3 = 1;
    
    pwm1_Init(5000);						//5kHz PWM signal
    TRISC = 0x00;							//PORT is output for PWM
    PORTC = 0x00;
    
    while(1) {
        for(i = 0 ; i < 1024 ; i++) {
            pwm1_duty(i);
            __delay_ms(10);
        }
        for(i = 1023 ; i >= 0 ; i--) {
            pwm1_duty(i);
            __delay_ms(10);
        }
        
    }
    return;
}
