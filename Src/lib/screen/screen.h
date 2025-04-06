#include "main.h"

#ifndef PAINT_H
#define PAINT_H

extern SPI_HandleTypeDef hspi1;

#define LCD_CS_SET (LCD_CS_GPIO_Port->BSRR = 1U << 0)
#define LCD_CLK_SET (LCD_CLK_GPIO_Port->BSRR = 1U << 10)
#define LCD_DC_SET (LCD_DC_GPIO_Port->BSRR = 1U << 2)
#define LCD_RST_SET (LCD_RST_GPIO_Port->BSRR = 1U << 1)

#define LCD_CS_RST (LCD_CS_GPIO_Port->BSRR = 1U << (16 + 0))
#define LCD_CLK_RST (LCD_CLK_GPIO_Port->BSRR = 1U << (16 + 10))
#define LCD_DC_RST (LCD_DC_GPIO_Port->BSRR = 1U << (16 + 2))
#define LCD_RST_RST (LCD_RST_GPIO_Port->BSRR = 1U << (16 + 1))

/*COMMANDS*/
#define SOFTWARE_RESET 0x01
#define READ_DISPLAY_IDS 0x04
#define READ_DISPLAY_STATUS 0x09
#define READ_DISPLAY_POWER_MODE 0x0A
#define READ_MADCTL 0x0B
#define READ_DISPLAY_PIXEL_FORMAT 0x0C
#define READ_DISPLAY_IMAGE_FORMAT 0x0D
#define READ_DISPLAY_SIGNAL_MODE 0x0E
#define READ_DISPLAY_SELF_DIAGNOSTIC_RESULT 0x0F
#define MODE_SLEEP_IN 0x10
#define MODE_SLEEP_OUT 0x11
#define MODE_PARTIAL_ON 0x12
#define MODE_NORMAL_DISPLAY_ON 0x13
#define MODE_DISPLAY_INVERSION_OFF 0x20
#define MODE_DISPLAY_INVERSION_ON 0x21
#define GAMMA_SET 0x26
#define DISPLAY_OFF 0x28
#define DISPLAY_ON 0x29
#define ADDRESS_COLUMN_SET 0x2A
#define ADDRESS_PAGE_SET 0x2B
#define MEMORY_WRITE 0x2C
#define COLOR_SET 0x2D
#define MEMORY_READ 0x2E
#define PARTIAL_AREA 0x30
#define PIXEL_FORMAT_SET 0x3A
#define MEMORY_ACCESS_CONTROL 0x36
#define IDLE_MODE_OFF 0x38
#define IDLE_MODE_ON 0x39
#define MEMORY_WRITE_CONTINUE 0x3C
#define READ_MEMORY_CONTINUE 0x3E
#define RGB_INTERFACE_CONTROL 0xB0
#define FRAME_CONTROL_N_MODE 0xB1
#define FRAME_CONTROL_I_MODE 0xB2
#define ENTRY_MODE_SET 0xB7
#define INTERFACE_CONTROL 0xF6
#define POWER_CONTROL 0XCF
#define DRIVER_TIMING_CONTROL_A 0XE8
#define DRIVER_TIMING_CONTROL_B 0XEA
#define POWER_ON_SEQUENCE_CONTROL 0xED
#define ENABLE_3G 0XF2
#define PUMP_RATIO_CONTROL 0XF7
#define NOP 0x00
/*
 * RGB DATA FORMAT:
 * MSB: R-5bit | G-6bit | B-5bit LSB.
 * */


#define START_BIT  0b10000000 // HIGH
#define X_POSITION 0b01010000 // 101
#define Y_POSITION 0b00010000 // 001
#define MODE_12BIT 0b00001000 // LOW
#define MODE_8BIT  0b00001000 // HIGH
#define MODE_DFR   0b00000111 // LOW
#define T_CS_SET GPIOB->BSRR = (1U << 12)
#define T_CS_RESET GPIOB->BSRR = (1U << (12 + 16))
#define T_IRQ_SET (GPIOA->BSRR = (1U << 8))
#define T_IRQ_RESET (GPIOA->BSRR = (1U << (8 + 16)))
#define T_IRQ (GPIOA->IDR & (1 << 8))
#define T_Y_H (120 - 14)

#define T_X_C1 1600
#define T_X_C2 1050
#define T_X_C3 500

#define T_Y_R1 880
#define T_Y_R2 680
#define T_Y_R3 540
#define T_Y_R4 370
#define ERROR_X 150
#define ERROR_Y 60

typedef struct{
	uint8_t X_;
	uint8_t Y_;
}Pressed;


typedef struct{
	int value;
	int data;
	int temp_set;
	char c[30];
	bool valid;
	bool rst;
	bool set;
	uint8_t n;
}Button;

extern Button button;
void scan(SPI_HandleTypeDef *spi, UART_HandleTypeDef *uart, Button *button, Pressed *pressed,bool print);
void read_col(Pressed *pressed, uint16_t *x);
void read_row(Pressed *pressed, uint16_t *x);
void get_button(Button *button, Pressed *pressed);



void WRITE_COMMAND(uint8_t command);
void WRITE_DATA(uint8_t data);
void WRITE_DATA_16B(uint16_t *color);

void READ_COMMAND(uint8_t *command);
void READ_DATA(uint8_t *data);

//void SCREEN_INIT(Screen *screen);
//void SCREEN_RESET(Screen *screen);

//void GET_IDS(uint8_t ids[3]);

//void SET_WINDOW(Screen *screen);
#endif
