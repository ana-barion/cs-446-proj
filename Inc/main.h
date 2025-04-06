/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "serial_printing.h"
#include "DS18B20.h"
#include "timer_us.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim10;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DS18B20 ds18b20_terminal;
extern DS18B20 ds18b20_hot;
extern bool temperature_control_enable;
extern float temperature_set;
extern uint8_t command;
extern float cold_water_temperature;
extern float hot_water_temperature;
extern float terminal_water_temperature;
extern uint8_t flag;
//extern uint8_t act;
#include "temperature_control.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void ESP_HandleMessage(const char* msg);

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* flag */
#define SCAN_PAD 0x80

/* act */
#define TEMP_UPDATE 0x01
#define TEMP_GET_TEMP_SET 0x02
#define TEMP_GET_VALV_APROX 0x04
#define TEMP_CONTROL_TEMP 0x08

/* command */
#define START	 0x01
#define IDLE	 0x02

/* page */
#define SCREEN_PAGE1 0x01
#define SCREEN_PAGE2 0x02
#define SCREEN_PAGE3 0x04
#define SCREEN_PAGE4 0x08


#define VALVE_ADJUST_COLD 0x10
#define VALVE_ADJUST_HOT 0x20
#define VALVE_ADJUST_STOP 0x30

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define SET_NEW_TEMP 			0x10000
#define READ_TERMINAL_TEMP		0x20000
#define READ_COLD_TEMP			0x30000
#define READ_HOT_TEMP			0x40000


#define RUNNING					0x01000000
#define IDLED					0x02000000
#define delay_ms 				HAL_Delay

typedef struct{
	uint8_t err[100];
	uint8_t err_value;
}ERR;

typedef struct{
	ERR err[15];
}ERR_STRING;

typedef struct{
	bool mode_8;
	bool mode_16;
	uint32_t width;
	uint32_t height;
	uint32_t start_x;
	uint32_t end_x;
	uint32_t start_y;
	uint32_t end_y;
	uint8_t command;
	uint8_t *buffer;
	uint8_t setxcmd;
	uint8_t setycmd;
	uint8_t wramcmd;
	uint16_t data;
	uint16_t pixel_color;
	uint16_t background_color;
}Screen;


/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_CS_Pin GPIO_PIN_0
#define LCD_CS_GPIO_Port GPIOH
#define Valve_M1_Pin GPIO_PIN_0
#define Valve_M1_GPIO_Port GPIOC
#define Valve_M2_Pin GPIO_PIN_1
#define Valve_M2_GPIO_Port GPIOC
#define Valve_M3_Pin GPIO_PIN_2
#define Valve_M3_GPIO_Port GPIOC
#define Valve_EN_Pin GPIO_PIN_3
#define Valve_EN_GPIO_Port GPIOC
#define Valve_RST_Pin GPIO_PIN_4
#define Valve_RST_GPIO_Port GPIOC
#define Valve_CLK_Pin GPIO_PIN_5
#define Valve_CLK_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_2
#define LCD_DC_GPIO_Port GPIOB
#define T_CS_Pin GPIO_PIN_12
#define T_CS_GPIO_Port GPIOB
#define Valve_CCW_Pin GPIO_PIN_6
#define Valve_CCW_GPIO_Port GPIOC
#define Valve_LATCH_Pin GPIO_PIN_7
#define Valve_LATCH_GPIO_Port GPIOC
#define Valve_TQ_Pin GPIO_PIN_8
#define Valve_TQ_GPIO_Port GPIOC
#define LCD_T_DIN_Pin GPIO_PIN_15
#define LCD_T_DIN_GPIO_Port GPIOA
#define Valve_ALERT_Pin GPIO_PIN_10
#define Valve_ALERT_GPIO_Port GPIOC
#define OneWire_Pin GPIO_PIN_5
#define OneWire_GPIO_Port GPIOB
#define ESP_EN_Pin GPIO_PIN_8
#define ESP_EN_GPIO_Port GPIOB
#define LCD_CSB9_Pin GPIO_PIN_9
#define LCD_CSB9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ERROR_COLD_WATER "Cold Water out of acceptable temperature inlet."
#define ERROR_HOT_WATER "Hot Water out of acceptable temperature inlet."

#define ERROR_TEMPERATURE_SET "Not a valid input temperature."
extern char error_msg_[100];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
