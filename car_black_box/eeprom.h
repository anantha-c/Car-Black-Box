/* 
 * File:   eeprom.h
 * Author: anant
 *
 * Created on 3 October, 2026, 5:09 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

extern unsigned char events[16];
extern unsigned char orginal_pass[4];
extern unsigned char user_password[4];
//#define EVENT_COUNT 10;

void write_EEprom(unsigned char index, unsigned char *data);
void read_EEprom(unsigned char index, unsigned char *data);
void store(void);
void view_log(void);
void clear_log(void);
void download(void);
void set_time(void);
void change_password(void);

#endif	/* EEPROM_H */

