/* 
 * File:   digital_keypad.h
 * Author: anant
 *
 * Created on 1 October, 2026, 8:18 PM
 */

#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H

#define LEVEL 0
#define STATE 1


#define SW1 0x3E
#define SW2 0X3D
#define SW3 0X3B
#define SW4 0x37
#define SW5 0x2F
#define SW6 0x1F

#define ALL_RELEASED 0x3F
void init_dks(void);
unsigned char read_dks(unsigned char mode);
#endif	/* DIGITAL_KEYPAD_H */

