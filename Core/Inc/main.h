/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
  
#include "stm32g0xx_hal.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
  
#include "string.h"
#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>
#include "App_RAM.h"
#include "Misc_Function.h"
#include "I2C_RTC.h"
#include "stm32g0xx_it.h"
#include "SW_I2C.h"
//#include "i2c.h"
#include "iwdg.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
  
extern I2C_HandleTypeDef hi2c1;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define UART1_BAUDRATE   9600
#define UART2_BAUDRATE   9600

#define UART1_TX_PIN    GPIO_PIN_9                                              //PA9
#define UART1_TX_PORT   GPIOA

#define UART1_RX_PIN    GPIO_PIN_10                                             //PA10
#define UART1_RX_PORT   GPIOA

#define UART2_TX_PIN    GPIO_PIN_2                                              //PA2 
#define UART2_TX_PORT   GPIOA

#define UART2_RX_PIN    GPIO_PIN_3                                              //PA3
#define UART2_RX_PORT   GPIOA
  
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

void Error_Handler(void);

/* USER CODE BEGIN EFP */

#define SET_DATA     DATA1_GPIO_Port        -> BSRR = DATA1_Pin
#define SET_DATA2    DATA2_GPIO_Port        -> BSRR = DATA2_Pin
#define SET_LATCH    COL_LAT_IN_GPIO_Port   -> BSRR = COL_LAT_IN_Pin
#define SET_CLK      COL_CLK_IN_GPIO_Port   -> BSRR = COL_CLK_IN_Pin
#define DISP_ENB     DISP_ENB_GPIO_Port     -> BRR = DISP_ENB_Pin

#define TOGGLE_OFF   DOT_GPIO_Port          -> BRR = (uint32_t)DOT_Pin

#define RST_DATA     DATA1_GPIO_Port        -> BRR = (uint32_t)DATA1_Pin
#define RST_DATA2    DATA2_GPIO_Port        -> BRR = (uint32_t)DATA2_Pin
#define RST_LATCH    COL_LAT_IN_GPIO_Port   -> BRR = (uint32_t)COL_LAT_IN_Pin
#define RST_CLK      DISP_ENB_GPIO_Port     -> BRR = (uint32_t)COL_CLK_IN_Pin
#define DISP_DSB     DISP_ENB_GPIO_Port     -> BSRR = (uint32_t)DISP_ENB_Pin 

#define TOGGLE_ON    DOT_GPIO_Port          -> BSRR = DOT_Pin      


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/


#define COL_LAT_IN_Pin                                    LL_GPIO_PIN_0         //PA0
#define COL_LAT_IN_GPIO_Port                              GPIOA

#define COL_CLK_IN_Pin                                    LL_GPIO_PIN_1         //PA1
#define COL_CLK_IN_GPIO_Port                              GPIOA

#define DATA1_Pin                                         LL_GPIO_PIN_4         //PA4
#define DATA1_GPIO_Port                                   GPIOA

#define DATA2_Pin                                         LL_GPIO_PIN_5         //PAG
#define DATA2_GPIO_Port                                   GPIOA

#define DISP_ENB_Pin                                      LL_GPIO_PIN_6         //PA6
#define DISP_ENB_GPIO_Port                                GPIOA

#define DOT_Pin                                           LL_GPIO_PIN_7         //PA7
#define DOT_GPIO_Port                                     GPIOA

#define INT_Pin                                           LL_GPIO_PIN_0         //PB0
#define INT_GPIO_Port                                     GPIOB

#define GPIO_12_24_Pin                                    LL_GPIO_PIN_1         //PB1
#define GPIO_12_24_GPIO_Port                              GPIOB

#define HH_TEN_Pin                                        LL_GPIO_PIN_2         //PB2
#define HH_TEN_GPIO_Port                                  GPIOB

#define HH_UNIT_Pin                                       LL_GPIO_PIN_10        //PB10
#define HH_UNIT_GPIO_Port                                 GPIOB

#define MM_TEN_Pin                                        LL_GPIO_PIN_11        //PB11
#define MM_TEN_GPIO_Port                                  GPIOB

#define MM_UNIT_Pin                                       LL_GPIO_PIN_12        //PB12
#define MM_UNIT_GPIO_Port                                 GPIOB

#define SS_TEN_Pin                                        LL_GPIO_PIN_13        //PB13
#define SS_TEN_GPIO_Port                                  GPIOB

#define SS_UNIT_Pin                                       LL_GPIO_PIN_14        //PB14
#define SS_UNIT_GPIO_Port                                 GPIOB

#define PRG_Pin                                           LL_GPIO_PIN_15        //PB15
#define PRG_GPIO_Port                                     GPIOB

#define DEC_Pin                                           LL_GPIO_PIN_11        //PA11
#define DEC_GPIO_Port                                     GPIOA

#define INC_Pin                                           LL_GPIO_PIN_12        //PA12
#define INC_GPIO_Port                                     GPIOA

#define SWD3_Pin                                          LL_GPIO_PIN_13        //PA13
#define SWD3_GPIO_Port                                    GPIOA

#define SWC2_Pin                                          LL_GPIO_PIN_14        //PA14
#define SWC2_GPIO_Port                                    GPIOA

#define GPS_ON_Pin                                        LL_GPIO_PIN_15        //PA15
#define GPS_ON_GPIO_Port                                  GPIOA

#define TEST_Pin                                          LL_GPIO_PIN_5         //PB5
#define TEST_GPIO_Port                                    GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
