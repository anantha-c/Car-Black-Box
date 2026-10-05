/*
 * File:   adc.c
 * Author: anant
 *
 * Created on 1 October, 2026, 8:02 PM
 */


#include <xc.h>

#define _XTAL_FREQ 20000000

void init_adc(void){
    
    TRISA = 1;
    PORTA = 0X00;
    
    ADCON0 = 0b00000001;
    ADCON1 = 0b11001110;
    
}

unsigned int read_adc(void){
    
    __delay_us(20);
    
    GO =1;
    
    while(nDONE);
    
    return ((ADRESH << 8) | ADRESL );
}