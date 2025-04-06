#ifndef INC_ESP_COMM_H_
#define INC_ESP_COMM_H_

#include "main.h"

void ESP_Init(void);
void ESP_Send(const char *cmd);
void ESP_ProcessByte(uint8_t byte);

void USART1_IRQHandler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /*