/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * Created on      : 24-Feb-2026
  * Author          : Rohit Jadhav
  * Hex Version     : IO-Card-Rohit.hex (1Mbps)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "engine.h"
#include "operations.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc2;

CAN_HandleTypeDef hcan1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
CAN_RxHeaderTypeDef rxHeader; //CAN Bus Transmit Header
CAN_TxHeaderTypeDef txHeader; //CAN Bus Receive Header
uint8_t canRX[8] = {0,0,0,0,0,0,0,0};  //CAN Bus Receive Buffer
CAN_FilterTypeDef canfil; //CAN Bus Filter
uint32_t canMailbox; //CAN Bus Mail box variable
uint8_t j=0;
uint32_t  x=0;
unsigned char c=0;
unsigned char Card[4]={0x04,0x00,0x00,0x00};
int receive_flag; // detection of received message on CAN
unsigned int operation,pin_no,pin_dir,pin_status; //Detection of operation
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC2_Init(void);
static void MX_CAN1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ADC_ch0()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
void ADC_ch3()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  HAL_Delay(500);
  MX_ADC2_Init();
  MX_CAN1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  card_status();
	
  canfil.FilterBank = 0;
	canfil.FilterMode = CAN_FILTERMODE_IDMASK;
	canfil.FilterFIFOAssignment = CAN_RX_FIFO0;
	canfil.FilterIdHigh =(0x7D0 + Card[3]) <<5;
	canfil.FilterIdLow = 0;
	canfil.FilterMaskIdHigh = 0xffff;
	canfil.FilterMaskIdLow = 0;
	canfil.FilterScale = CAN_FILTERSCALE_32BIT;
	canfil.FilterActivation = ENABLE;
	canfil.SlaveStartFilterBank = 14;

	txHeader.DLC = 8;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.StdId = 0X030; //fixed ID for OS to receive
	txHeader.ExtId = 0x02;
	txHeader.TransmitGlobalTime = DISABLE;

	HAL_CAN_ConfigFilter(&hcan1,&canfil);
	if(HAL_CAN_Start(&hcan1)==HAL_OK)
	{
		HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
	}
	else
	{
		HAL_CAN_Stop(&hcan1);
		HAL_Delay(100);
		HAL_CAN_Start(&hcan1);
	}

	HAL_GPIO_WritePin(GPIOG, D_Pin, 0);
	HAL_GPIO_WritePin(GPIOG, C_Pin, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    if(receive_flag==1)
				{
					switch(operation)
					{
					case 1:
						HAL_GPIO_WritePin(GPIOG, C_Pin, 0);//changed to C_Pin from GPIO_PIN_12
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 0);//changed to D_Pin from GPIO_PIN_13
						single_read();
						break;
					case 2:
						HAL_GPIO_WritePin(GPIOG, C_Pin, 0);
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 0);
						single_write();
						break;
					case 3:
						HAL_GPIO_WritePin(GPIOG, C_Pin, 0);
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 0);
						multiple_read();
						break;
					case 4:
						HAL_GPIO_WritePin(GPIOG, C_Pin, 0);
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 0);
						card_status();
						break;
					case 5:
						HAL_GPIO_WritePin(GPIOG, C_Pin, 0);
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 0);
						reinit();
						break;
					case 6:
					  HAL_GPIO_WritePin(GPIOG, C_Pin, 1);
		        HAL_GPIO_WritePin(GPIOG, D_Pin, 1);
						analog_read();
						break;
					}
					receive_flag = 0;
				}
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ENABLE;
  hadc2.Init.ContinuousConvMode = ENABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 2;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, S0_Pin|S1_Pin|S2_Pin|S3_Pin
                          |A_Pin|B_Pin|Control_25_Pin|Control_26_Pin
                          |Control_27_Pin|Control_23_Pin|Control_24_Pin|Control_10_Pin
                          |Control_11_Pin|Control_12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Control_28_Pin|Control_16_Pin|Control_17_Pin|Control_46_Pin
                          |Control_47_Pin|Control_48_Pin|Control_55_Pin|Control_52_Pin
                          |Control_53_Pin|Control_54_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Control_18_Pin|Control_19_Pin|Control_20_Pin|Control_56_Pin
                          |Control_57_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Control_21_Pin|Control_22_Pin|Control_9_Pin|Control_29_Pin
                          |Control_30_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, Control_13_Pin|Control_14_Pin|Control_39_Pin|Control_40_Pin
                          |Control_41_Pin|Control_42_Pin|Control_43_Pin|Control_44_Pin
                          |Control_45_Pin|Control_58_Pin|Control_59_Pin|Control_60_Pin
                          |C_Pin|D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Control_15_Pin|Control_1_Pin|Control_2_Pin|Control_3_Pin
                          |Control_4_Pin|Control_5_Pin|Control_6_Pin|Control_7_Pin
                          |Control_8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Control_31_Pin|Control_32_Pin|Control_33_Pin|Control_34_Pin
                          |Control_35_Pin|Control_36_Pin|Control_37_Pin|Control_38_Pin
                          |Control_49_Pin|Control_50_Pin|Control_51_Pin|Control_64_Pin
                          |Control_61_Pin|Control_62_Pin|Control_63_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Card_Select_1_Pin Card_Select_2_Pin Card_Select_3_Pin Card_Select_4_Pin
                           Card_Select_5_Pin */
  GPIO_InitStruct.Pin = Card_Select_1_Pin|Card_Select_2_Pin|Card_Select_3_Pin|Card_Select_4_Pin
                          |Card_Select_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : Card_Select_6_Pin */
  GPIO_InitStruct.Pin = Card_Select_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Card_Select_6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Input_1_Pin Input_2_Pin */
  GPIO_InitStruct.Pin = Input_1_Pin|Input_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : S0_Pin S1_Pin S2_Pin S3_Pin
                           A_Pin B_Pin Control_25_Pin Control_26_Pin
                           Control_27_Pin Control_23_Pin Control_24_Pin Control_10_Pin
                           Control_11_Pin Control_12_Pin */
  GPIO_InitStruct.Pin = S0_Pin|S1_Pin|S2_Pin|S3_Pin
                          |A_Pin|B_Pin|Control_25_Pin|Control_26_Pin
                          |Control_27_Pin|Control_23_Pin|Control_24_Pin|Control_10_Pin
                          |Control_11_Pin|Control_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_28_Pin Control_16_Pin Control_17_Pin Control_46_Pin
                           Control_47_Pin Control_48_Pin Control_55_Pin Control_52_Pin
                           Control_53_Pin Control_54_Pin */
  GPIO_InitStruct.Pin = Control_28_Pin|Control_16_Pin|Control_17_Pin|Control_46_Pin
                          |Control_47_Pin|Control_48_Pin|Control_55_Pin|Control_52_Pin
                          |Control_53_Pin|Control_54_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_18_Pin Control_19_Pin Control_20_Pin Control_56_Pin
                           Control_57_Pin */
  GPIO_InitStruct.Pin = Control_18_Pin|Control_19_Pin|Control_20_Pin|Control_56_Pin
                          |Control_57_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_21_Pin Control_22_Pin Control_9_Pin Control_29_Pin
                           Control_30_Pin */
  GPIO_InitStruct.Pin = Control_21_Pin|Control_22_Pin|Control_9_Pin|Control_29_Pin
                          |Control_30_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_13_Pin Control_14_Pin Control_39_Pin Control_40_Pin
                           Control_41_Pin Control_42_Pin Control_43_Pin Control_44_Pin
                           Control_45_Pin Control_58_Pin Control_59_Pin Control_60_Pin
                           C_Pin D_Pin */
  GPIO_InitStruct.Pin = Control_13_Pin|Control_14_Pin|Control_39_Pin|Control_40_Pin
                          |Control_41_Pin|Control_42_Pin|Control_43_Pin|Control_44_Pin
                          |Control_45_Pin|Control_58_Pin|Control_59_Pin|Control_60_Pin
                          |C_Pin|D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_15_Pin Control_1_Pin Control_2_Pin Control_3_Pin
                           Control_4_Pin Control_5_Pin Control_6_Pin Control_7_Pin
                           Control_8_Pin */
  GPIO_InitStruct.Pin = Control_15_Pin|Control_1_Pin|Control_2_Pin|Control_3_Pin
                          |Control_4_Pin|Control_5_Pin|Control_6_Pin|Control_7_Pin
                          |Control_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : Control_31_Pin Control_32_Pin Control_33_Pin Control_34_Pin
                           Control_35_Pin Control_36_Pin Control_37_Pin Control_38_Pin
                           Control_49_Pin Control_50_Pin Control_51_Pin Control_64_Pin
                           Control_61_Pin Control_62_Pin Control_63_Pin */
  GPIO_InitStruct.Pin = Control_31_Pin|Control_32_Pin|Control_33_Pin|Control_34_Pin
                          |Control_35_Pin|Control_36_Pin|Control_37_Pin|Control_38_Pin
                          |Control_49_Pin|Control_50_Pin|Control_51_Pin|Control_64_Pin
                          |Control_61_Pin|Control_62_Pin|Control_63_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1)
{

	if(HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &rxHeader, canRX)==HAL_OK){
		  operation = canRX[0];
			pin_no = canRX[1];
			pin_dir = canRX[2];
			pin_status = canRX[3];
			receive_flag = 1;
	}
	else{
		Error_Handler();
	}
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1); //not calling HAL_CAN_IRQHandler(&hcan1); 24-Feb-26 Rohit
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
