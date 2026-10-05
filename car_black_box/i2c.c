/*
 * File:   i2c.c
 * Author: anant
 *
 * Created on 1 October, 2026, 4:22 PM
 */


#include <xc.h>
#include "i2c.h"

void init_i2c(unsigned long baud){
    
    SMP = 1;
    
    //SSPCON1 REGISTER
    
    
    
    SSPM3 = 1;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;
    
    SSPADD =  (unsigned char) ((FOSC/(4*baud)) -1) ;
    
    SSPEN =1;
     
}

void i2c_wait_for_idle(void){
    
    while(R_nW ||  (SSPCON2 & 0x1F));
}

void i2c_start(void){
    i2c_wait_for_idle();
    SEN =1;
    
}

void i2c_repeat_start(void){
    i2c_wait_for_idle();
    RSEN =1;
}

void i2c_stop(void){
    i2c_wait_for_idle();
    PEN =1;
}


unsigned char read_i2c(unsigned char ack){
    i2c_wait_for_idle();
    RCEN = 1;
    unsigned char data;
    while(!BF);
    data = SSPBUF;
    
    if(ack == 1){
        ACKDT = 1;
    }
    else{
        ACKDT = 0;
    }
    ACKEN = 1;
    
    return data;
}

unsigned char write_i2c(unsigned char data){
    i2c_wait_for_idle();
    
    SSPBUF = data;
    while(!BF);
    return !ACKSTAT;
}