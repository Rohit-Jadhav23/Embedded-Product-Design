#include "Engine.h"
#include "operations.h"
#include "stm32f4xx_hal.h"
#include "main.h"
extern ADC_HandleTypeDef hadc2;
extern unsigned int address;
//char counter1=0;
unsigned char result[8];
unsigned char Status=0;
unsigned char  A=0;
char Pin_Status=0;
char counter1=0;
extern unsigned char Card[4];
extern unsigned int operation,pin_no,pin_dir,pin_status; //Detection of operation
unsigned char pin;
unsigned int i=1;
unsigned int select_status1=0,select_status2=0,select_status3=0,select_status4=0,select_status5=0,select_status6=0;
uint32_t avg[2],buffer[2];
float Adc_value=0,Avg_ADC_Value=0,Vout1_ref=0;
unsigned int resistance=0,resistance_val=0;
float Vout1=0,voltage=4.99;
float Vout2=0;
uint32_t adc_val[2];
/*==============================for calculating resistance value===================*/

void ADC_read()
{

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, 1);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 1);
//			ADC_ch0();
//			HAL_ADC_Start(&hadc2);
//			HAL_ADC_PollForConversion(&hadc2,200);
//			adc_val[0]=HAL_ADC_GetValue(&hadc2);
//			HAL_ADC_Stop(&hadc2);

			ADC_ch3();
			HAL_ADC_Start(&hadc2);
			HAL_ADC_PollForConversion(&hadc2,200);
			adc_val[1]=HAL_ADC_GetValue(&hadc2);
			HAL_ADC_Stop(&hadc2);

			//Vout2= 0.00080810546875*adc_val[1];//   0.0008056640625
//	Vout1_ref=R3+R4;
//	Vout1= (Vout1_ref/R4)*Vout2;
//	resistance=(Rref*voltage)/Vout1;
//	resistance_val=resistance-Rref;
//	Vout2=0;
//	Vout1=0;
//	resistance=0;
//	Avg_ADC_Value=0;
//	Adc_value=0;
	//HAL_ADC_Stop(&hadc2);
//		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, 0);
//		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 0);


}
/*==================================================================================*/
/*===========================to find which number of card is selected=================*/
unsigned short int Card_select(void)
{
	Pin_Status=HAL_GPIO_ReadPin(GPIOE,Card_Select_1_Pin);
	if(Pin_Status==0)
	{
		counter1=counter1+1;
	}
	Pin_Status=HAL_GPIO_ReadPin(GPIOE,Card_Select_2_Pin);
	if(Pin_Status==0)
	{
		counter1=counter1+2;
	}
	Pin_Status=HAL_GPIO_ReadPin(GPIOE,Card_Select_3_Pin);
	if(Pin_Status==0)
	{
		counter1=counter1+4;
	}
	Pin_Status=HAL_GPIO_ReadPin(GPIOE,Card_Select_4_Pin);

	if(Pin_Status==0)
	{
		counter1=counter1+8;
	}

	Pin_Status=HAL_GPIO_ReadPin(GPIOE,Card_Select_5_Pin);
	if(Pin_Status==0)
	{
		counter1=counter1+16;
	}
	Pin_Status=HAL_GPIO_ReadPin(GPIOC,Card_Select_6_Pin);

	if(Pin_Status==0)
	{
		counter1=counter1+32;
	}
	Card[3]= counter1;

	counter1=0;
	return(counter1);


}
/*================================================================================*/

/*------------------------Line selection (S0,S1,S2,S2,A,B)------------------  */
void Select_line(unsigned int address)
{
	select_status1 = (address &  0x0001);
	select_status2 = (address &  0x0002) >> 1;
	select_status3 = (address &  0x0004) >> 2;
	select_status4 = (address &  0x0008) >> 3;
	select_status5 = (address &  0x0010) >> 4;
	select_status6 = (address &  0x0020) >> 5;
	//GPIOF->ODR= ((GPIOF->ODR & 0XFF00)|(address)<<2);
	if(select_status1==1)
	{
		HAL_GPIO_WritePin(GPIOF, S0_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, S0_Pin, 0);
	}
	if(select_status2==1)
	{
		HAL_GPIO_WritePin(GPIOF, S1_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, S1_Pin, 0);
	}
	if(select_status3==1)
	{
		HAL_GPIO_WritePin(GPIOF, S2_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, S2_Pin, 0);
	}
	if(select_status4==1)
	{
		HAL_GPIO_WritePin(GPIOF, S3_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, S3_Pin, 0);
	}
	if(select_status5==1)
	{
		HAL_GPIO_WritePin(GPIOF, B_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, B_Pin, 0);
	}
	if(select_status6==1)
	{
		HAL_GPIO_WritePin(GPIOF, A_Pin, 1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, A_Pin, 0);
	}

	for(int i=0;i<=300;i++)
	{

	}
	//HAL_Delay(1);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void diode_test()
{
	Control_line(1);
	Select_line(1);
	Read_pin();
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
unsigned char Read_pin()
{

	pin= HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0);
	return pin;

}
/*--------------------------------------------------------------------------*/
void led_test()
{
	Control_line(0);
	HAL_Delay(1000);
	Control_line(65);
	HAL_Delay(1000);
}
/*--------------------------------------------------------------------------*/

/*==========================Check board=====================================*/
void card_read()
{
	unsigned char i;
	A=0;

		/*------------------------------------for  1- 8 signal pins-----------------------*/
	for(i=1;i<=8;i++)
	{

		Select_line(i-1);
		Status =Read_pin();
		A=A|Status<<(i-1);
	}
	result[0]= A ;
	A=0;
		/*------------------------------------for  9- 16 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+8);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[1]= A ;
		A=0;
		/*------------------------------------for  17- 24 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+16);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[2]= A ;
		A=0;
		/*------------------------------------for  25- 32 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+24);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[3]= A ;
		A=0;
		/*------------------------------------for  33- 40 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+32);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[4]= A ;
		A=0;
		/*------------------------------------for  41- 48 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+40);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[5]= A ;
		A=0;
		/*------------------------------------for  49- 56 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+48);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[6]= A ;
		A=0;
		/*------------------------------------for  57- 64 signal pins-----------------------*/
		for(i=1;i<=8;i++)
		{
			Select_line(i-1+56);
			Status =Read_pin();
			A=A|Status<<(i-1);
		}
		result[7]= A ;
		A=0;
}
/*===============================================================================*/
void Control_line(unsigned int address)
{
	//pin_status=1;
	switch(address)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOE, Control_1_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_2_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_3_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_4_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_5_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_6_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_7_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_8_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_9_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_10_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_11_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_12_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_13_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_14_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_15_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_16_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_17_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_18_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_19_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_20_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_21_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_22_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_23_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_24_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_25_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_26_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_27_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_28_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_29_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_30_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_31_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_32_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_33_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_34_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_35_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_36_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_37_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_38_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_39_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_40_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_41_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_42_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_43_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_44_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_45_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_46_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_47_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_48_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_49_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_50_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_51_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_52_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_53_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_54_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_55_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_56_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_57_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_58_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_59_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_60_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_61_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_62_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_63_Pin, 0);
		HAL_GPIO_WritePin(GPIOE, Control_64_Pin, 0);
		break;
	case 1:
		if(pin_status==1)    // check pin status for set pin high or low
		{
			HAL_GPIO_WritePin(GPIOE, Control_1_Pin, 1); //Set pin High
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_1_Pin, 0); // set pin low
		}
		break;
	case 2:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_2_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_2_Pin, 0);
		}
		break;

	case 3:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_3_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_3_Pin, 0);
		}
		break;
	case 4:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_4_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_4_Pin, 0);
		}
		break;
	case 5:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_5_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_5_Pin, 0);
		}
		break;
	case 6:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_6_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_6_Pin, 0);
		}
		break;

	case 7:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_7_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_7_Pin, 0);
		}
		break;
	case 8:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_8_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_8_Pin, 0);
		}
		break;
	case 9:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOB, Control_9_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, Control_9_Pin, 0);
		}
		break;
	case 10:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_10_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_10_Pin, 0);
		}
		break;
	case 11:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_11_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_11_Pin, 0);
		}
		break;
	case 12:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_12_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_12_Pin, 0);
		}
		break;
	case 13:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_13_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_13_Pin, 0);
		}
		break;
	case 14:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_14_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_14_Pin, 0);
		}
		break;
	case 15:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOE, Control_15_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, Control_15_Pin, 0);
		}
		break;
	case 16:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_16_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_16_Pin, 0);
		}
		break;
	case 17:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_17_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_17_Pin, 0);
		}
		break;
	case 18:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOA, Control_18_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, Control_18_Pin, 0);
		}
		break;
	case 19:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOA, Control_19_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, Control_19_Pin, 0);
		}
		break;
	case 20:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOA, Control_20_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, Control_20_Pin, 0);
		}
		break;
	case 21:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOB, Control_21_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, Control_21_Pin, 0);
		}
		break;
	case 22:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOB, Control_22_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, Control_22_Pin, 0);
		}
		break;
	case 23:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_23_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_23_Pin, 0);
		}
		break;
	case 24:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_24_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_24_Pin, 0);
		}
		break;
	case 25:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_25_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_25_Pin, 0);
		}
		break;
	case 26:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_26_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_26_Pin, 0);
		}
		break;
	case 27:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOF, Control_27_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOF, Control_27_Pin, 0);
		}
		break;
	case 28:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_28_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_28_Pin, 0);
		}
		break;
	case 29:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOB, Control_29_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, Control_29_Pin, 0);
		}
		break;
	case 30:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOB, Control_30_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, Control_30_Pin, 0);
		}
		break;
	case 31:
		if(pin_status==1)    // check pin status for set pin high or low
		{
			HAL_GPIO_WritePin(GPIOD, Control_31_Pin, 1); //Set pin High
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_31_Pin, 0); // set pin low
		}
		break;
	case 32:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_32_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_32_Pin, 0);
		}
		break;

	case 33:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_33_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_33_Pin, 0);
		}
		break;
	case 34:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_34_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_34_Pin, 0);
		}
		break;
	case 35:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_35_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_35_Pin, 0);
		}
		break;
	case 36:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_36_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_36_Pin, 0);
		}
		break;

	case 37:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_37_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_37_Pin, 0);
		}
		break;
	case 38:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_38_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_38_Pin, 0);
		}
		break;
	case 39:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_39_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_39_Pin, 0);
		}
		break;
	case 40:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_40_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_40_Pin, 0);
		}
		break;
	case 41:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_41_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_41_Pin, 0);
		}
		break;
	case 42:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_42_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_42_Pin, 0);
		}
		break;
	case 43:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_43_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_43_Pin, 0);
		}
		break;
	case 44:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_44_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_44_Pin, 0);
		}
		break;
	case 45:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_45_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_45_Pin, 0);
		}
		break;
	case 46:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_46_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_46_Pin, 0);
		}
		break;
	case 47:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_47_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_47_Pin, 0);
		}
		break;
	case 48:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_48_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_48_Pin, 0);
		}
		break;
	case 49:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_49_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_49_Pin, 0);
		}
		break;
	case 50:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_50_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_50_Pin, 0);
		}
		break;
	case 51:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_51_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_51_Pin, 0);
		}
		break;
	case 52:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_52_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_52_Pin, 0);
		}
		break;
	case 53:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_53_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_53_Pin, 0);
		}
		break;
	case 54:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_54_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_54_Pin, 0);
		}
		break;
	case 55:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOC, Control_55_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC, Control_55_Pin, 0);
		}
		break;
	case 56:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOA, Control_56_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, Control_56_Pin, 0);
		}
		break;
	case 57:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOA, Control_57_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, Control_57_Pin, 0);
		}
		break;
	case 58:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_58_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_58_Pin, 0);
		}
		break;
	case 59:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_59_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_59_Pin, 0);
		}
		break;
	case 60:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOG, Control_60_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, Control_60_Pin, 0);
		}
		break;
	case 61:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_61_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_61_Pin, 0);
		}
		break;

	case 62:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_62_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_62_Pin, 0);
		}
		break;

	case 63:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_63_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_63_Pin, 0);
		}
		break;
	case 64:
		if(pin_status==1)
		{
			HAL_GPIO_WritePin(GPIOD, Control_64_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, Control_64_Pin, 0);
		}
		break;


	case 65:
		HAL_GPIO_WritePin(GPIOE, Control_1_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_2_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_3_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_4_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_5_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_6_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_7_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_8_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_9_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_10_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_11_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_12_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_13_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_14_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_15_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_16_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_17_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_18_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_19_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_20_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_21_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_22_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_23_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_24_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_25_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_26_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_27_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_28_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_29_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_30_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_31_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_32_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_33_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_34_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_35_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_36_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_37_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_38_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_39_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_40_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_41_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_42_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_43_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_44_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_45_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_46_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_47_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_48_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_49_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_50_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_51_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_52_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_53_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_54_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_55_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_56_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_57_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_58_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_59_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_60_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_61_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_62_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_63_Pin, 1);
		HAL_GPIO_WritePin(GPIOE, Control_64_Pin, 1);
		break;


	}

}
