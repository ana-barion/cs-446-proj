#include "screen.h"
#include "serial_printing.h"
#include <math.h>

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

void WRITE_COMMAND(uint8_t command){
	//uint8_t a[] = {'L', 'u', 'c', 'a', 's'};
	LCD_CS_RST;
	LCD_DC_RST;
	HAL_SPI_Transmit(&hspi1, &command, sizeof(uint8_t), 0xFFFF);
	//print_hex_f_array(&huart2, a, sizeof(a), false, false, true, false, false);
	LCD_CS_SET;
}

void WRITE_DATA(uint8_t data){
	LCD_CS_RST;
	LCD_DC_SET;
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
	LCD_CS_SET;
}

void WRITE_DATA_16B(uint16_t *color){
    LCD_CS_RST;
    LCD_RST_SET;
    uint8_t id = 0xF8;
    HAL_SPI_Transmit(&hspi1,&id, 1, 1000);
    id = 0x00;
    HAL_SPI_Transmit(&hspi1, &id, 1, 1000);
    LCD_CS_SET;
}

void READ_COMMAND(uint8_t *command){
	LCD_CS_RST;
	LCD_DC_RST;
	HAL_SPI_Receive(&hspi1, command, 1, 1000);
	LCD_CS_SET;
}

void READ_DATA(uint8_t *data){
	LCD_CS_RST;
	LCD_DC_SET;
	HAL_SPI_Receive(&hspi1, data, sizeof(data), 1000);
	LCD_CS_SET;
}

void SCREEN_RESET(Screen *screen){
	LCD_RST_RST;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);
}

void SCREEN_INIT(Screen *screen){
	WRITE_COMMAND(POWER_CONTROL);
	WRITE_DATA(NOP);
	WRITE_DATA(0x81); //0xC1
	WRITE_DATA(0X30);
	WRITE_COMMAND(POWER_ON_SEQUENCE_CONTROL);
	WRITE_DATA(0x55);
	WRITE_DATA(0x01);
	WRITE_DATA(0X23);
	WRITE_DATA(0X01);
	WRITE_COMMAND(DRIVER_TIMING_CONTROL_A);
	WRITE_DATA(0x84);
	WRITE_DATA(0x11);
	WRITE_DATA(0x7A);
	WRITE_COMMAND(0xCB);
	WRITE_DATA(0x39);
	WRITE_DATA(0x2C);
	WRITE_DATA(0x00);
	WRITE_DATA(0x34);
	WRITE_DATA(0x02);
	WRITE_COMMAND(PUMP_RATIO_CONTROL);
	WRITE_DATA(0x10);
	WRITE_COMMAND(DRIVER_TIMING_CONTROL_B);
	WRITE_DATA(0x66);
	WRITE_DATA(0x00);
	WRITE_COMMAND(0xC0);    //Power control
	WRITE_DATA(0x1B);   //VRH[5:0]
	WRITE_COMMAND(0xC1);    //Power control
	WRITE_DATA(0x12);   //SAP[2:0];BT[3:0] 0x01
	WRITE_COMMAND(0xC5);    //VCM control
	WRITE_DATA(0x08); 	 //30
	WRITE_DATA(0x26); 	 //30
	WRITE_COMMAND(0xC7);    //VCM control2
	WRITE_DATA(0XB7);
	WRITE_COMMAND(0x36);    // Memory Access Control
	WRITE_DATA(0x08);
	WRITE_COMMAND(PIXEL_FORMAT_SET);
	WRITE_DATA(0x55);
	WRITE_COMMAND(0xB1);
	WRITE_DATA(0x00);
	WRITE_DATA(0x1A);
	WRITE_COMMAND(0xB6);    // Display Function Control
	WRITE_DATA(0x0A);
	WRITE_DATA(0xA2);
	WRITE_COMMAND(ENABLE_3G);    // 3Gamma Function Disable
	WRITE_DATA(NOP);
	WRITE_COMMAND(GAMMA_SET);    //Gamma curve selected
	WRITE_DATA(0x01);
	WRITE_COMMAND(0xE0);    //Set Gamma
	WRITE_DATA(0x0F);
	WRITE_DATA(0x1D);
	WRITE_DATA(0x1A);
	WRITE_DATA(0x0A);
	WRITE_DATA(0x0D);
	WRITE_DATA(0x07);
	WRITE_DATA(0x49);
	WRITE_DATA(0X66);
	WRITE_DATA(0x3B);
	WRITE_DATA(0x07);
	WRITE_DATA(0x11);
	WRITE_DATA(0x01);
	WRITE_DATA(0x09);
	WRITE_DATA(0x05);
	WRITE_DATA(0x04);
	WRITE_COMMAND(0XE1);    //Set Gamma
	WRITE_DATA(0x00);
	WRITE_DATA(0x18);
	WRITE_DATA(0x1D);
	WRITE_DATA(0x02);
	WRITE_DATA(0x0F);
	WRITE_DATA(0x04);
	WRITE_DATA(0x36);
	WRITE_DATA(0x13);
	WRITE_DATA(0x4C);
	WRITE_DATA(0x07);
	WRITE_DATA(0x13);
	WRITE_DATA(0x0F);
	WRITE_DATA(0x2E);
	WRITE_DATA(0x2F);
	WRITE_DATA(0x05);
	WRITE_COMMAND(ADDRESS_PAGE_SET);
	WRITE_DATA(0x00);
	WRITE_DATA(0x00);
	WRITE_DATA(0x01);
	WRITE_DATA(0x3f);
	WRITE_COMMAND(ADDRESS_COLUMN_SET);
	WRITE_DATA(0x00);
	WRITE_DATA(0x00);
	WRITE_DATA(0x00);
	WRITE_DATA(0xef);
	WRITE_COMMAND(MODE_SLEEP_OUT); //Exit Sleep
	delay_ms(120);
	WRITE_COMMAND(MODE_NORMAL_DISPLAY_ON);
	WRITE_COMMAND(DISPLAY_ON); //display on
}

void GET_IDS(uint8_t ids[3]){
	WRITE_COMMAND(READ_DISPLAY_IDS);
	READ_DATA(ids);
	//HAL_SPI_Receive(&hspi2, ids, 3*sizeof(uint8_t), 1000);
}

void SET_WINDOW(Screen *screen){
	WRITE_COMMAND(screen->setxcmd);
	WRITE_DATA(screen->start_x>>8);
	WRITE_DATA(0x00FF&screen->start_x);
	WRITE_DATA(screen->end_x>>8);
	WRITE_DATA(0x00FF&screen->end_x);

	WRITE_COMMAND(screen->setycmd);
	WRITE_DATA(screen->start_y>>8);
	WRITE_DATA(0x00FF&screen->start_y);
	WRITE_DATA(screen->end_y>>8);
	WRITE_DATA(0x00FF&screen->end_y);
}


void scan(SPI_HandleTypeDef *spi, UART_HandleTypeDef *uart, Button *button, Pressed *pressed,bool print){
	uint8_t a;
	uint8_t data_X[2];
	uint8_t data_Y[2];
	char buffer_X[50];
	char buffer_Y[50];
	char buff[10];
	char temp1[30];
	char temp2[30];
	char buffer[50];

	/* X-POSITION*/
	a = 0x00;
	a = START_BIT | X_POSITION;
	//a = START_BIT | X_POSITION | MODE_8BIT;
	memset(buffer_X, 0, sizeof(buffer_X));
	memset(buffer_Y, 0, sizeof(buffer_Y));
	memset(data_X, 0, sizeof(data_X));
	memset(data_Y, 0, sizeof(data_Y));
	memset(buffer, 0, sizeof(buffer));
	memset(buff, 0, sizeof(buff));
	memset(temp1, 0, sizeof(temp1));
	memset(temp2, 0, sizeof(temp2));

	T_CS_RESET; // @suppress("Statement has no effect")
	//T_IRQ_RESET;
	HAL_SPI_Transmit(&hspi4, &a, 1, 1000); // @suppress("Statement has no effect")
	//T_IRQ_SET;
	//T_IRQ_RESET;
	HAL_SPI_Receive(&hspi4, data_X, 2, 1000);
	T_CS_SET;
	//T_IRQ_SET;

	HAL_Delay(100);
	/* Y-POSITION*/
	a = 0x00;
	a = START_BIT | Y_POSITION;
	//a = START_BIT | Y_POSITION | MODE_8BIT;
	T_CS_RESET;
	//T_IRQ_RESET;
	HAL_SPI_Transmit(&hspi4, &a, 1, 1000);
	//T_IRQ_SET;
	//T_IRQ_RESET;
	HAL_SPI_Receive(&hspi4, data_Y, 2, 1000);
	T_CS_SET;
	//T_IRQ_SET;

	uint16_t r_X = data_X[0] << 4 | (data_X[1] >> 3);
	uint16_t r_Y = data_Y[0] << 4 | (data_Y[1] >> 3);
	read_col(pressed, &r_X);
	read_row(pressed, &r_Y);

	get_button(button, pressed);
	int n = button->value;
	if(n != -1){
		if(n > -1){
			button->valid = true;
		}

		else{
			button->valid = true;
			button->rst = true;
			if(n == -3){button->set = true;}
		}
	}

	if(print && n != -1){
		sprintf(buffer_X, "X_-> %X | X_ANL -> %d ", pressed->X_, r_X);
		print_hex_f_array(uart, (uint8_t *)buffer_X, 1000, false, false, false, true, false);

		sprintf(buffer_Y, "Y_ -> %X | Y_ANL -> %d", pressed->Y_, r_Y);
		print_hex_f_array(uart, (uint8_t *)buffer_Y, 1000, false, false, false, true, false);
	}
}

void read_col(Pressed *pressed, uint16_t *x){
	pressed->X_ = 0x00;
	if(*x > (T_X_C1 - ERROR_X) && *x < (T_X_C1 + ERROR_X)){
		pressed->X_ |= (0x04);
	}
	else if(*x > (T_X_C2 - ERROR_X) && *x < (T_X_C2 + ERROR_X)){
		pressed->X_ |= (0x02);
	}
	else if(*x > (T_X_C3 - ERROR_X) && *x < (T_X_C3 + ERROR_X)){
		pressed->X_ |= (0x01);
	}
}

void read_row(Pressed *pressed, uint16_t *y){
	pressed->Y_ = 0x00;
	if(*y > (T_Y_R1 - ERROR_Y) && *y < (T_Y_R1 + ERROR_Y)){
		pressed->Y_ |= (0x80);
	}
	else if(*y > (T_Y_R2 - ERROR_Y) && *y < (T_Y_R2 + ERROR_Y)){
		pressed->Y_ |= (0x40);
	}
	else if(*y > (T_Y_R3 - ERROR_Y) && *y < (T_Y_R3 + ERROR_Y)){
		pressed->Y_ |= (0x20);
	}
	else if(*y > (T_Y_R4 - ERROR_Y) && *y < (T_Y_R4 + ERROR_Y)){
		pressed->Y_ |= (0x10);
	}
}

void get_button(Button *button, Pressed *pressed){
	memset(button->c, 0 , strlen(button->c));
	uint8_t r = (pressed->X_ | pressed->Y_);
	/*		(4) (2) (1)
	 * (8)   1    2   3
	 * (4)   4    5   6
	 * (2)   7    8   9
	 * (1)  clr   0   set
	 * */
	switch (r){
		case 0x84:
			button->value = 1;
			break;
		case 0x82:
			button->value = 2;
			break;
		case 0x81:
			button->value = 3;
			break;
		case 0x44:
			button->value = 4;
			break;
		case 0x42:
			button->value = 5;
			break;
		case 0x41:
			button->value = 6;
			break;

		case 0x24:
			button->value = 7;
			break;
		case 0x22:
			button->value = 8;
			break;
		case 0x21:
			button->value = 9;
			break;

		case 0x14:
			button->value = -2;
			break;
		case 0x12:
			button->value = 0;
			break;
		case 0x11:
			button->value = -3;
			break;
		default:
			button->value = -1;
			break;
	}
}
