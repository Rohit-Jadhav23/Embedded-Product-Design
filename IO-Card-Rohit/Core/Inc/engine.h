/*
engine.h

Created on : 24-Feb-2026
Author     : Rohit Jadhav
*/

#ifndef __ENGINE_H
#define __ENGINE_H
#define R3 				100000
#define R4				100000
void Select_line(unsigned int address);
void Control_line(unsigned int address);
unsigned char Read_pin(void);
void card_read();
void led_test();
void diode_test();
void ADC_read();
unsigned short int Card_select(void);
#endif