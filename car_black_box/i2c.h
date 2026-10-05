/* 
 * File:   i2c.h
 * Author: anant
 *
 * Created on 1 October, 2026, 5:02 PM
 */

#ifndef I2C_H
#define	I2C_H
#define FOSC 20000000UL
void init_i2c(unsigned long baud);
void i2c_wait_for_idle(void);
void i2c_start(void);
void i2c_repeat_start(void);
void i2c_stop(void);
unsigned char read_i2c(unsigned char ack);
unsigned char write_i2c(unsigned char data);


#endif	/* I2C_H */

