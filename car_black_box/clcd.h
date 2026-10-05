/* 
 * File:   clcd.h
 * Author: anant
 *
 * Created on 1 October, 2026, 4:19 PM
 */

#ifndef CLCD_H
#define	CLCD_H

#define INST_MODE 0
#define DATA_MODE 1

#define LINE1(Y) (0x80 + Y)
#define LINE2(Y) (0xC0 + Y)

void clcd_write(unsigned char value , unsigned char mode);
void init_instr(void);
void init_clcd(void);
void clcd_putch(unsigned char data , unsigned char addr);
void clcd_print(unsigned char *data,unsigned char addr);

#endif	/* CLCD_H */

