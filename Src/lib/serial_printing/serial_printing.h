/*
 * serial_printing.h
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */

#ifndef SRC_LIB_SERIAL_PRINTING_SERIAL_PRINTING_H_
#define SRC_LIB_SERIAL_PRINTING_SERIAL_PRINTING_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_hex_f_array(UART_HandleTypeDef* uart, uint8_t* msg, uint32_t Timeout
		, bool s_space, bool s_line, bool e_space, bool e_line, bool hex_format);


#endif /* SRC_LIB_SERIAL_PRINTING_SERIAL_PRINTING_H_ */
