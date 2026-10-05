/* 
 * File:   rtc.h
 * Author: anant
 *
 * Created on 1 October, 2026, 5:51 PM
 */

#ifndef RTC_H
#define	RTC_H

#define SEC_ADDR 0X00
#define MIN_ADDR 0x01
#define HR_ADDR 0x02

#define WRITE_SLAVE 0b11010000
#define READ_SLAVE  0b11010001

void init_rtc(void);
unsigned char read_rtc(unsigned char read_addr);
void write_rtc(unsigned char addr,unsigned char data);
#endif	/* RTC_H */

