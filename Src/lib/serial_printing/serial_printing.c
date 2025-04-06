/*
 * serial_printing.c
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */
#include "main.h"


void print_f_array(UART_HandleTypeDef* uart, uint8_t* msg, uint32_t Timeout
		, bool s_space, bool s_line, bool e_space, bool e_line){
}

void print_hex_f_array(UART_HandleTypeDef* uart, uint8_t* pToArray, uint32_t Timeout
		, bool s_space, bool s_line, bool e_space, bool e_line, bool hex_format){

		int len = strlen((char *)pToArray);
		char hexStr[3];
		for (int i=0; i< len; i++){
			if (hex_format){
				sprintf(hexStr, "%02X", pToArray[i]);
				HAL_UART_Transmit(uart, (uint8_t *)hexStr,2,Timeout);}
			else{HAL_UART_Transmit(uart, &pToArray[i],1,Timeout);}

			if (s_space){
				uint8_t space_char = ' ';
				HAL_UART_Transmit(uart, &space_char, 1, Timeout);}

			else if (s_line){
				uint8_t space_char = '\n';
				HAL_UART_Transmit(uart, &space_char, 1, Timeout);}
		}
		if (e_space){
			uint8_t eol_char = ' ';
			HAL_UART_Transmit(uart, &eol_char, 1, Timeout);}

		else if (e_line){
			const char* eol_char = "\r\n";
			HAL_UART_Transmit(uart, (uint8_t *)eol_char, 1, Timeout);

		}
}
