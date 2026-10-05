/*
 * File:   clcd.c
 * Author: anant
 *
 * Created on 1 October, 2026, 4:05 PM
 */


#include <xc.h>
#include "clcd.h"
#define _XTAL_FREQ 20000000


void clcd_write(unsigned char value , unsigned char mode){
    
    RE2 = mode;
    PORTD = value;
    
    RE1 = 1;
    __delay_us(10);
    RE1 = 0;
    __delay_us(10);
}
void init_instr(void){
    
    __delay_us(30);
    clcd_write(0x33,INST_MODE);
    __delay_us(4100);
    clcd_write(0x33,INST_MODE);
    __delay_us(100);
    clcd_write(0x33,INST_MODE);
    __delay_us(100);
    
    clcd_write(0x38,INST_MODE); // 8bit   2lines
    __delay_ms(50);
    clcd_write(0x01,INST_MODE);
    __delay_ms(3);
    clcd_write(0x0C,INST_MODE); //display on
    __delay_ms(20);
    
}

void init_clcd(void){
    
    TRISD = 0X00;
    PORTD = 0X00;
    
    TRISE1 = 0;
    TRISE2 = 0 ;
    
    RE1 = 0;
    RE2 = 0;
    
    init_instr();
}

void clcd_putch(unsigned char data , unsigned char addr){
    
    clcd_write(addr,INST_MODE);
    clcd_write(data,DATA_MODE);
}

void clcd_print(unsigned char *data,unsigned char addr){
    clcd_write(addr,INST_MODE);
    
    while(*data){
        clcd_write(*data,DATA_MODE);
        data++;
    }
}