/*
 * File:   digital_keypad.c
 * Author: anant
 *
 * Created on 1 October, 2026, 8:12 PM
 */


#include <xc.h>
#include "digital_keypad.h"
void init_dks(void){
    
    TRISB = TRISB | 0X3F;
    PORTB = 0X00;
    
}

unsigned char read_dks(unsigned char mode){
    unsigned char key = PORTB & 0x3F;
    static unsigned char once = 1;
    if(mode == LEVEL){
        return key;
    }
    else{
        
        
        if((key != ALL_RELEASED) && once){
            once =0;
            return key;
        }
        else if(key == ALL_RELEASED){
            once =1;
        }
    }
    return ALL_RELEASED;
}