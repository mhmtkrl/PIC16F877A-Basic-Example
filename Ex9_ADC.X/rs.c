#include "rs.h"

void UART_config(const long int baudrate, char speed) {
    unsigned int X;
    RCSTAbits.SPEN = 1;     					//Serial port is activated
    TXSTAbits.SYNC = 0;     					//Async mode
    TXSTAbits.TXEN = 1;     					//Tx is enabled
    RCSTAbits.CREN = 1;     					//Continous mode for receiver
    TRISCbits.TRISC7 = 1;      					//Rx pin
    TRISCbits.TRISC6 = 0;						//Tx pin

    PIE1bits.RCIE = 1;  						//UART interrupt event is activated
    INTCONbits.PEIE = 1;						//PEripheral interrupts are enabled
    INTCONbits.GIE = 1;							//Allowed all activated interrupt
    
    if(speed == 0) {
        X = (_XTAL_FREQ / (baudrate * 64)) - 1;
    }
    else {
        X = (_XTAL_FREQ / (baudrate * 16)) - 1;
        TXSTAbits.BRGH = 1;     				//HighSpeed
    }
    SPBRG = X;									//Baudrate is calculated using this equation X = (_XTAL_FREQ / (baudrate * 16/64)) - 1;
}

void send_char(char data) {
    while(!TXSTAbits.TRMT);
    TXREG = data;
}

read_char() {
    while(!PIR1bits.RCIF);
    return RCREG;
}

void send_string(char *text) {
    int i;
    for(i = 0; text[i] != '\0' ; i++) {
        send_char(text[i]);
    }
}