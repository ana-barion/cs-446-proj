/*
 * ds18b20.h
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */

#ifndef SRC_LIB_DS18B20_LIB_DS18B20_H_
#define SRC_LIB_DS18B20_LIB_DS18B20_H_

#include "main.h"

			/****************** DS18B20 DEFINITIONS****************************/
#define DS18B20_PORT GPIOB
#define DS18B20_PIN GPIO_PIN_5
#define MAX_DS18B20 3
#define N_DS18B20_SERIAL_NUMBER_BYTES 9 // 1 for null
#define COLD_TEMP 18

typedef struct{
	uint8_t SERIAL_NUMBER [N_DS18B20_SERIAL_NUMBER_BYTES];
	float temperature;
	int pos;
}DS18B20;


							/******* GENERAL FUNCTIONS **********/
void ds18b20_init();
int ds18b20_test(UART_HandleTypeDef *uart);
void ds18b20_drive_LOW();
void ds18b20_release_HIGH();
void ds18b20_write_0();
void ds18b20_write_1();
bool ds18b20_start();
float ds18b20_get_temperature(DS18B20* sensor, bool skip_rom, UART_HandleTypeDef* uart);
void ds18b20_write_byte(uint8_t command);
uint8_t* ds18b20_read(bool temperature_reading, int n_i, int n_j, UART_HandleTypeDef* uart);
char* ds18b20_read_temperature(DS18B20* sensor, bool skip_rom, UART_HandleTypeDef* uart);
							/********** ROM FUNCTIONS **********/
int8_t ds18b20_search_ROM(uint8_t device_rom[MAX_DS18B20][N_DS18B20_SERIAL_NUMBER_BYTES], UART_HandleTypeDef* uart); /* 0xF0*/
uint8_t* ds18b20_read_ROM(); /* 0x33*/
void ds18b20_match_ROM(DS18B20* sensor); /* 0x55*/
void ds18b20_skip_ROM(); /* 0xCC*/
void ds18b20_alarm_search(); /* 0xEC*/

						/********** FUNCTION COMMANDS **********/
void ds18b20_convert_T(); /* 0x44*/
void ds18b20_write_scratchpad(); /* 0x4E*/
uint8_t* ds18b20_read_scratchpad(bool skip_rom, DS18B20* sensor,UART_HandleTypeDef* uart); /* 0xBE*/
void ds18b20_copy_scratchpad(); /* 0x48*/
void ds18b20_recall(); /* 0xB8*/
void ds18b20_read_power_supply(); /* 0xB4*/

void ds18b20_run(TIM_HandleTypeDef *htim);
void ds18b20_idle(TIM_HandleTypeDef *htim);
					/********** COMMANDS **********/
#define DS18B20_SEARCH_ROM 0xF0 // 11110000
#define DS18B20_READ_ROM 0x33 // 00110011
#define DS18B20_MATCH_ROM 0x55 //01010101
#define DS18B20_SKIP_ROM 0xCC //11001100
#define DS18B20_ALARM_SEARCH 0xEC // 11101100

#define DS18B20_CONVERT_T 0x44 // 01000100
#define DS18B20_WRITE_SCRATCHPAD 0x4E // 01001110
#define DS18B20_READ_SCRATCHPAD 0xBE // 10111110
#define DS18B20_COPY_SCRATCHPAD 0x48 // 01001000
#define DS18B20_RECALL 0xB8 // 10111000
#define DS18B20_READ_POWER_SUPPLY 0xB4 // 10110100





#endif /* SRC_LIB_DS18B20_LIB_DS18B20_H_ */
