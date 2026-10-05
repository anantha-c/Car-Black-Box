/*
 * File:   eeprom.c
 * Author: anant
 *
 * Created on 3 October, 2026, 5:07 PM
 */


#include <xc.h>
#include<stdio.h>
#include<string.h>
#include "eeprom.h"
#include "clcd.h"
#include "digital_keypad.h"

#define _XTAL_FREQ 20000000

void write_EEprom(unsigned char index, unsigned char *data){
    
    for(unsigned char i=0;i<16;i++){
        eeprom_write(0x00 + ((index * 16) + i), data[i]);
    }
}

void read_EEprom(unsigned char index, unsigned char *data)
{
    unsigned char i;

    for(i = 0; i < 16; i++)
    {
        data[i] = eeprom_read((index * 16) + i);
    }
}

unsigned char event_size =0;

void store(void){
    
    unsigned char i;
    unsigned char event[16];
    if(event_size <10){
        write_EEprom(event_size, events);
        event_size++;
    }
    else{
        //shift events
        

        for(i = 0; i < 9; i++)
        {
            read_EEprom(i + 1, event);
            write_EEprom(i, event);
        }
        
        write_EEprom(9, events);    
    }  
  
}

void view_log(void){
    
    
    unsigned char event1[16];
    unsigned char event2[16];
    
    
    unsigned char ind =0;
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    
    if(event_size == 0)
    {
        clcd_print("NO EVENTS", LINE1(3));
        __delay_ms(2000);

        clcd_write(0x01, INST_MODE);
        __delay_ms(5);

        return;
    }
    
    clcd_print("displaying",LINE1(2));
    clcd_print("EVENTS",LINE2(4));
    __delay_ms(2000);
    
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    
    while(1){
        
        read_EEprom(ind, event1);

        if(ind + 1 < event_size)
        {
            read_EEprom(ind + 1, event2);
        }
        clcd_print(event1, LINE1(0));

        if(ind + 1 < event_size)
        {
            clcd_print(event2, LINE2(0));
        }
        
        
        while(read_dks(LEVEL) != ALL_RELEASED);

        unsigned char key = read_dks(STATE);
        
        
        
        if(key == SW4 && ind >=2){
            ind = ind -2;
        }
        else if(key == SW5 && (ind +2)<event_size){
            ind = ind +2;
        }
        else if(key == SW6){
            clcd_write(0x01,INST_MODE);
            __delay_ms(5);
            return ;
        }
           
    }
}

void clear_log(void){
    unsigned char i;
    unsigned char empty[16] = {0};

    for(i = 0; i < 10; i++)
    {
        write_EEprom(i, empty);
    }

    event_size = 0;

    clcd_write(0x01, INST_MODE);
    __delay_ms(2);

    clcd_print("LOG CLEARED", LINE1(2));
    __delay_ms(2000);

    clcd_write(0x01, INST_MODE);
    __delay_ms(2);
    
    return;
}

void download(void){
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    
    clcd_print("displaying",LINE1(2));
    clcd_print("EVENTS",LINE2(4));
    __delay_ms(2000);
            
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    return;
    
}
void set_time(void){
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    
    clcd_print("displaying",LINE1(2));
    clcd_print("EVENTS",LINE2(4));
    __delay_ms(2000);
            
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    return;
    
}

void change_password(void)
{
    unsigned char new_password[4];
    unsigned char confirm_password[4];
    unsigned char index;
    unsigned char key;

    /* ---------------- NEW PASSWORD ---------------- */

    clcd_write(0x01, INST_MODE);
    __delay_ms(2);

    clcd_print("New Password", LINE1(2));

    index = 0;

    while(index < 4)
    {
        while(read_dks(LEVEL) != ALL_RELEASED);
        __delay_ms(20);
        key = read_dks(STATE);

        if(key == SW4)
        {
            new_password[index] = '1';
            clcd_putch('*', LINE2(5 + index));
            index++;
        }
        else if(key == SW5)
        {
            new_password[index] = '0';
            clcd_putch('*', LINE2(5 + index));
            index++;
        }
    }

    /* ---------------- CONFIRM PASSWORD ---------------- */

    clcd_write(0x01, INST_MODE);
    __delay_ms(2);

    clcd_print("Confirm Pass", LINE1(1));

    index = 0;

    while(index < 4)
    {
        while(read_dks(LEVEL) != ALL_RELEASED);
        __delay_ms(20);
        key = read_dks(STATE);

        if(key == SW4)
        {
            confirm_password[index] = '1';
            clcd_putch('*', LINE2(5 + index));
            index++;
        }
        else if(key == SW5)
        {
            confirm_password[index] = '0';
            clcd_putch('*', LINE2(5 + index));
            index++;
        }
    }

    /* ---------------- COMPARE ---------------- */

    if(memcmp(new_password, confirm_password, 4) == 0)
    {
        /* Passwords match */

        for(index = 0; index < 4; index++)
        {
            orginal_pass[index] = new_password[index];
        }

        clcd_write(0x01, INST_MODE);
        __delay_ms(2);

        clcd_print("Password", LINE1(4));
        clcd_print("Changed", LINE2(4));

        __delay_ms(2000);
    }
    else
    {
        /* Passwords don't match */

        clcd_write(0x01, INST_MODE);
        __delay_ms(2);

        clcd_print("Password", LINE1(4));
        clcd_print("Mismatch", LINE2(4));

        __delay_ms(2000);
    }

    clcd_write(0x01, INST_MODE);
    __delay_ms(2);
    
    
    return;
}