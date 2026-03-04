/*
 * operations.c
 *
 *  Created on: 24-Feb-2026
 *      Author: Rohit Jadhav
 */

#include "main.h"
#include "operations.h"
#include "stm32f4xx_hal.h"
#include "Engine.h"
extern uint32_t canMailbox;
extern CAN_HandleTypeDef hcan1;
extern CAN_RxHeaderTypeDef rxHeader; //CAN Bus Transmit Header
extern CAN_TxHeaderTypeDef txHeader; //CAN Bus Receive Header
extern unsigned char pin;
extern unsigned char result[9];
extern unsigned char Card[4];
extern unsigned int operation,pin_no,pin_dir,pin_status; //Detection of operation
extern unsigned int resistance_val ;
extern uint32_t adc_val[2];

void single_read()
{
	uint8_t csend[] = {0x01,0x01,0x00,0x00};
	Control_line(pin_no);
	Select_line(pin_no-1);
	Read_pin();
	csend[3]=pin;
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,csend,&canMailbox);
}


void single_write()
{
	uint8_t csend[] = {operation,pin_no,0x00,0x00};
	//pin_no=1;
	Control_line(pin_no);
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,csend,&canMailbox);

}


void multiple_read()
{
	card_read();
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,result,&canMailbox);
}

void card_status()
{
	Card_select();
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,Card,&canMailbox);
	//Card[3]=0;
}

void reinit()
{
	uint8_t csend[] = {0x05,0x00,0x00,0x00};
	Control_line(0);
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,csend,&canMailbox);

}

void analog_read()
{
	//Control_line(1);
	Select_line(pin_no-1);
	ADC_read();
	uint8_t csend[] = {0x06,0x00,0x00,0x00};
	csend[2]= adc_val[1] >> 8 ;
	csend[3]=adc_val[1];
	HAL_CAN_AddTxMessage(&hcan1,&txHeader,csend,&canMailbox);
	adc_val[1]=0;

}









