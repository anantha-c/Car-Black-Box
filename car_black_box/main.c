/*
 * File:   main.c
 * Author: anant
 *
 * Created on 1 October, 2026, 4:03 PM
 */


#include <xc.h>
#include "i2c.h"
#include "clcd.h"
#include "rtc.h"
#include "adc.h"
#include "digital_keypad.h"
#include "eeprom.h"
#include<string.h>
#include<stdio.h>

#define _XTAL_FREQ 20000000
#pragma config WDTE = OFF

unsigned char events[16];
unsigned char orginal_pass[4] = {'1','0','1','0'};
unsigned char user_password[4];


void init_config(){
    
    init_clcd();
    init_i2c(100000);
    init_adc();
    init_dks();
    init_rtc();
    
}
unsigned char clock_reg[3];

void get_time(void){
    clock_reg[0] = read_rtc(HR_ADDR);
    clock_reg[1] = read_rtc(MIN_ADDR);
    clock_reg[2] = read_rtc(SEC_ADDR);
    
    
}
unsigned char time[9];
void display_time(unsigned char *clock_reg){
    
    
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
    time[1] = (clock_reg[0] & 0x0F) + '0';
    
    time[2] = ':';
    
    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
    time[4] = (clock_reg[1] & 0x0F) + '0'; 
    
    time[5] = ':';
    
    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
    time[7] = (clock_reg[2] & 0x0F) + '0';
    time[8] = '\0';
    clcd_print(time,LINE2(0));
    __delay_us(100);
    
}

void password_check(void){
    clcd_write(0x01,INST_MODE);
    __delay_ms(2);
    unsigned char index =0;
    unsigned char fail_attempts =0;
    
    
    
    while(1){
        while(read_dks(LEVEL) != ALL_RELEASED);
        __delay_ms(20);
        unsigned char key = read_dks(STATE); 
        clcd_print("Enter Password",LINE1(0));
        
        if(key == SW4 && index < 4){
            user_password[index] = '1';
            clcd_putch('*',LINE2(5+index));
            index++;
        }
        else if(key == SW5 && index < 4){
            user_password[index] = '0';
            clcd_putch('*',LINE2(5+index));
            index++;
        }
        
        
        if(index == 4){
            __delay_ms(100);
            
            if(memcmp(orginal_pass,user_password,4) == 0){
                
                clcd_write(0x01,INST_MODE);
                __delay_ms(5);
                
                clcd_print("Unlocked!",LINE1(2));
                __delay_ms(2000);
                break;
            }
            
            else{
                fail_attempts++;
                index=0;
                if(fail_attempts == 4){
                    clcd_write(0x01,INST_MODE);
                    __delay_ms(5);

                    clcd_print("Locked!",LINE1(2));
                    
                    clcd_print("Retry in..10 s",LINE2(0));
                    __delay_ms(500);
                    clcd_print("Retry in..  s ",LINE2(0));
                    unsigned char ch = 9;
                    while(ch > 0){
                        clcd_putch((ch + '0'),LINE2(11));
                        ch--;
                        __delay_ms(1000);
                    }
                    clcd_putch(ch + '0',LINE2(11));
                     __delay_ms(1000);
                     
                     clcd_write(0x01,INST_MODE);
                    __delay_ms(5);
                   
                     
                    
                }
                else if(fail_attempts >0 && fail_attempts <4){
                    
                    clcd_write(0x01,INST_MODE);
                    __delay_ms(5);

                    clcd_print("Invalid PASS...D",LINE1(0));
                    clcd_putch(((4 - fail_attempts)+'0'),LINE2(1));
                    clcd_print("attempts left",LINE2(3));

                    __delay_ms(2000);
                    clcd_write(0x01,INST_MODE);
                    __delay_ms(5);
                }
            }
        }
        
    }
    return ;   
}
unsigned char menu[][14] = {
        "View         ",
        "clear        ",
        "download     ",
        "set time     ",
        "change p**d  "
        
    };
void goto_menu(void)
{
    clcd_write(0x01, INST_MODE);
    __delay_ms(2);

    password_check();
    
    while(read_dks(LEVEL) != ALL_RELEASED);
    __delay_ms(50);
    
    clcd_write(0x01, INST_MODE);
    __delay_ms(2);
    

    unsigned char ind = 0;

    while(1)
    {
        while(read_dks(LEVEL) != ALL_RELEASED);
        __delay_ms(20);
        unsigned char key = read_dks(STATE);

        
        
        if(ind%2==0){
            if(ind == 4){
                
                clcd_putch('*',LINE1(0));
                clcd_putch(' ',LINE2(0));
                clcd_print(menu[ind],LINE1(2));
                clcd_print("             ",LINE2(2));
            }
            clcd_putch('*',LINE1(0));
            clcd_putch(' ',LINE2(0));
            clcd_print(menu[ind],LINE1(2));
            clcd_print(menu[ind+1],LINE2(2));
        }
        else{
            clcd_putch(' ',LINE1(0));
            clcd_putch('*',LINE2(0));
            clcd_print(menu[ind-1],LINE1(2));
            clcd_print(menu[ind],LINE2(2));
        }
        
        
        if(key == SW1){
            switch(ind){
                case (0) : view_log(); break;
                case (1) : clear_log(); break;
                case (2) : download() ; break;
                case (3) : set_time(); break;
                case (4) : change_password();break;
                default : break;
            }
        }
        else if(key == SW4 && ind > 0)
        {
            
                ind--;
            
        }
        else if(key == SW5 && ind < 4)
        {
            
                ind++;
            
        }
        else if(key == SW6)
        {
            clcd_write(0x01, INST_MODE);
            __delay_ms(2);
            clcd_print("TIME      EV  SP",LINE1(0));
            return;
        }
        

        
    }
}



static const unsigned char gear[][3] = {
    "GN", "G1", "G2", "G3", "G4", "G5", "_C"
};
void dashboard(unsigned char key){
    
    
    
    get_time();
    display_time(clock_reg);
    
    unsigned int speed;
    speed = read_adc();
    speed = speed/10.23;
    
    static int i=0;
    if(key == SW1){
        i=6;
        sprintf((char *)events, "%s %s %02u", time, gear[i], speed);
        
        store();
    }
    else if(key == SW2 && i<6){
        i++;
        sprintf((char *)events, "%s %s %02u", time, gear[i], speed);
        store();
    }
    else if(key == SW3 && i>0){
        i--;
        sprintf((char *)events, "%s %s %02u", time, gear[i], speed);
        store();
    }
    else if(key == SW4){
        goto_menu();
    }
    clcd_print(gear[i],LINE2(10));
    
    
    clcd_putch((speed/10)+'0' , LINE2(14));
    clcd_putch((speed%10)+'0' , LINE2(15));
    __delay_us(100);
}
void main(void){
 
    init_config();
    
    clcd_print("Welcome!",LINE1(3));
    __delay_ms(1000);
    clcd_write(0x01,INST_MODE);
    __delay_ms(5);
    clcd_print("TIME      EV  SP",LINE1(0));
    
    unsigned char key;
    
    while(1){
        key = read_dks(STATE);
        
        dashboard(key);
        
    }
    return ;
    
}

