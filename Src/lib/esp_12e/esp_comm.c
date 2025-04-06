#include "esp_comm.h"
#include "main.h"  
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart1;
uint8_t esp_rx_byte;

#define ESP_RX_BUFFER_SIZE 64
static char esp_rx_buffer[ESP_RX_BUFFER_SIZE];
static uint8_t esp_rx_index = 0;

/**
 * @brief Initialize ESP communication
 */
void ESP_Init(void) {
    ESP_Send("AT");
    HAL_Delay(100);
    ESP_Send("AT+CWMODE=1");  // Station mode
    HAL_Delay(100);

    HAL_UART_Receive_IT(&huart1, &esp_rx_byte, 1);  // Start UART RX interrupt
}

/**
 * @brief Send a command to ESP with CRLF
 * @param cmd - null-terminated string (without CRLF)
 */
void ESP_Send(const char *cmd) {
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

/**
 * @brief Process each incoming byte to build complete message
 */
void ESP_ProcessByte(uint8_t byte) {
    if (esp_rx_index < ESP_RX_BUFFER_SIZE - 1) {
        esp_rx_buffer[esp_rx_index++] = byt