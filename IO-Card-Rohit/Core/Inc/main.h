/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Card_Select_1_Pin GPIO_PIN_2
#define Card_Select_1_GPIO_Port GPIOE
#define Card_Select_2_Pin GPIO_PIN_3
#define Card_Select_2_GPIO_Port GPIOE
#define Card_Select_3_Pin GPIO_PIN_4
#define Card_Select_3_GPIO_Port GPIOE
#define Card_Select_4_Pin GPIO_PIN_5
#define Card_Select_4_GPIO_Port GPIOE
#define Card_Select_5_Pin GPIO_PIN_6
#define Card_Select_5_GPIO_Port GPIOE
#define Card_Select_6_Pin GPIO_PIN_13
#define Card_Select_6_GPIO_Port GPIOC
#define Input_1_Pin GPIO_PIN_0
#define Input_1_GPIO_Port GPIOF
#define Input_2_Pin GPIO_PIN_1
#define Input_2_GPIO_Port GPIOF
#define S0_Pin GPIO_PIN_2
#define S0_GPIO_Port GPIOF
#define S1_Pin GPIO_PIN_3
#define S1_GPIO_Port GPIOF
#define S2_Pin GPIO_PIN_4
#define S2_GPIO_Port GPIOF
#define S3_Pin GPIO_PIN_5
#define S3_GPIO_Port GPIOF
#define A_Pin GPIO_PIN_6
#define A_GPIO_Port GPIOF
#define B_Pin GPIO_PIN_7
#define B_GPIO_Port GPIOF
#define Control_25_Pin GPIO_PIN_8
#define Control_25_GPIO_Port GPIOF
#define Control_26_Pin GPIO_PIN_9
#define Control_26_GPIO_Port GPIOF
#define Control_27_Pin GPIO_PIN_10
#define Control_27_GPIO_Port GPIOF
#define Control_28_Pin GPIO_PIN_0
#define Control_28_GPIO_Port GPIOC
#define Control_16_Pin GPIO_PIN_2
#define Control_16_GPIO_Port GPIOC
#define Control_17_Pin GPIO_PIN_3
#define Control_17_GPIO_Port GPIOC
#define Input_3_Pin GPIO_PIN_0
#define Input_3_GPIO_Port GPIOA
#define Input_3A3_Pin GPIO_PIN_3
#define Input_3A3_GPIO_Port GPIOA
#define Control_18_Pin GPIO_PIN_4
#define Control_18_GPIO_Port GPIOA
#define Control_19_Pin GPIO_PIN_5
#define Control_19_GPIO_Port GPIOA
#define Control_20_Pin GPIO_PIN_6
#define Control_20_GPIO_Port GPIOA
#define Control_21_Pin GPIO_PIN_0
#define Control_21_GPIO_Port GPIOB
#define Control_22_Pin GPIO_PIN_1
#define Control_22_GPIO_Port GPIOB
#define Control_23_Pin GPIO_PIN_11
#define Control_23_GPIO_Port GPIOF
#define Control_24_Pin GPIO_PIN_12
#define Control_24_GPIO_Port GPIOF
#define Control_10_Pin GPIO_PIN_13
#define Control_10_GPIO_Port GPIOF
#define Control_11_Pin GPIO_PIN_14
#define Control_11_GPIO_Port GPIOF
#define Control_12_Pin GPIO_PIN_15
#define Control_12_GPIO_Port GPIOF
#define Control_13_Pin GPIO_PIN_0
#define Control_13_GPIO_Port GPIOG
#define Control_14_Pin GPIO_PIN_1
#define Control_14_GPIO_Port GPIOG
#define Control_15_Pin GPIO_PIN_7
#define Control_15_GPIO_Port GPIOE
#define Control_1_Pin GPIO_PIN_8
#define Control_1_GPIO_Port GPIOE
#define Control_2_Pin GPIO_PIN_9
#define Control_2_GPIO_Port GPIOE
#define Control_3_Pin GPIO_PIN_10
#define Control_3_GPIO_Port GPIOE
#define Control_4_Pin GPIO_PIN_11
#define Control_4_GPIO_Port GPIOE
#define Control_5_Pin GPIO_PIN_12
#define Control_5_GPIO_Port GPIOE
#define Control_6_Pin GPIO_PIN_13
#define Control_6_GPIO_Port GPIOE
#define Control_7_Pin GPIO_PIN_14
#define Control_7_GPIO_Port GPIOE
#define Control_8_Pin GPIO_PIN_15
#define Control_8_GPIO_Port GPIOE
#define Control_9_Pin GPIO_PIN_10
#define Control_9_GPIO_Port GPIOB
#define Control_29_Pin GPIO_PIN_14
#define Control_29_GPIO_Port GPIOB
#define Control_30_Pin GPIO_PIN_15
#define Control_30_GPIO_Port GPIOB
#define Control_31_Pin GPIO_PIN_8
#define Control_31_GPIO_Port GPIOD
#define Control_32_Pin GPIO_PIN_9
#define Control_32_GPIO_Port GPIOD
#define Control_33_Pin GPIO_PIN_10
#define Control_33_GPIO_Port GPIOD
#define Control_34_Pin GPIO_PIN_11
#define Control_34_GPIO_Port GPIOD
#define Control_35_Pin GPIO_PIN_12
#define Control_35_GPIO_Port GPIOD
#define Control_36_Pin GPIO_PIN_13
#define Control_36_GPIO_Port GPIOD
#define Control_37_Pin GPIO_PIN_14
#define Control_37_GPIO_Port GPIOD
#define Control_38_Pin GPIO_PIN_15
#define Control_38_GPIO_Port GPIOD
#define Control_39_Pin GPIO_PIN_2
#define Control_39_GPIO_Port GPIOG
#define Control_40_Pin GPIO_PIN_3
#define Control_40_GPIO_Port GPIOG
#define Control_41_Pin GPIO_PIN_4
#define Control_41_GPIO_Port GPIOG
#define Control_42_Pin GPIO_PIN_5
#define Control_42_GPIO_Port GPIOG
#define Control_43_Pin GPIO_PIN_6
#define Control_43_GPIO_Port GPIOG
#define Control_44_Pin GPIO_PIN_7
#define Control_44_GPIO_Port GPIOG
#define Control_45_Pin GPIO_PIN_8
#define Control_45_GPIO_Port GPIOG
#define Control_46_Pin GPIO_PIN_6
#define Control_46_GPIO_Port GPIOC
#define Control_47_Pin GPIO_PIN_7
#define Control_47_GPIO_Port GPIOC
#define Control_48_Pin GPIO_PIN_8
#define Control_48_GPIO_Port GPIOC
#define Control_55_Pin GPIO_PIN_9
#define Control_55_GPIO_Port GPIOC
#define Control_56_Pin GPIO_PIN_8
#define Control_56_GPIO_Port GPIOA
#define Control_57_Pin GPIO_PIN_15
#define Control_57_GPIO_Port GPIOA
#define Control_52_Pin GPIO_PIN_10
#define Control_52_GPIO_Port GPIOC
#define Control_53_Pin GPIO_PIN_11
#define Control_53_GPIO_Port GPIOC
#define Control_54_Pin GPIO_PIN_12
#define Control_54_GPIO_Port GPIOC
#define Control_49_Pin GPIO_PIN_1
#define Control_49_GPIO_Port GPIOD
#define Control_50_Pin GPIO_PIN_2
#define Control_50_GPIO_Port GPIOD
#define Control_51_Pin GPIO_PIN_3
#define Control_51_GPIO_Port GPIOD
#define Control_64_Pin GPIO_PIN_4
#define Control_64_GPIO_Port GPIOD
#define Control_61_Pin GPIO_PIN_5
#define Control_61_GPIO_Port GPIOD
#define Control_62_Pin GPIO_PIN_6
#define Control_62_GPIO_Port GPIOD
#define Control_63_Pin GPIO_PIN_7
#define Control_63_GPIO_Port GPIOD
#define Control_58_Pin GPIO_PIN_9
#define Control_58_GPIO_Port GPIOG
#define Control_59_Pin GPIO_PIN_10
#define Control_59_GPIO_Port GPIOG
#define Control_60_Pin GPIO_PIN_11
#define Control_60_GPIO_Port GPIOG
#define C_Pin GPIO_PIN_12
#define C_GPIO_Port GPIOG
#define D_Pin GPIO_PIN_13
#define D_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
