/*
 * File:   rtc.c
 * Author: anant
 *
 * Created on 1 October, 2026, 5:35 PM
 */


#include <xc.h>
#include "i2c.h"
#include "rtc.h"

void init_rtc(void){
    
    unsigned char dummy;
    
    dummy = read_rtc(SEC_ADDR);
    dummy = dummy & 0x7F;
    
    write_rtc(SEC_ADDR,dummy);
}

unsigned char read_rtc(unsigned char read_addr){
    
    unsigned char data;
    
    i2c_start();
    write_i2c(WRITE_SLAVE);
    write_i2c(read_addr);
    i2c_repeat_start();
    write_i2c(READ_SLAVE);
    data = read_i2c(1);
    i2c_stop();
    
    return data;
}

void write_rtc(unsigned char addr,unsigned char data){
    
    i2c_start();
    write_i2c(WRITE_SLAVE);
    write_i2c(addr);
    
    
    write_i2c(data);
    i2c_stop();
}