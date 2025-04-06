/*
 * ds18b20.c
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */
#include "main.h"
GPIO_PinState ds18b20_status = GPIO_PIN_SET;

DS18B20 ds18b20_terminal = {
	.SERIAL_NUMBER = {0x28, 0x50, 0x3A, 0x85, 0x00, 0x00, 0x00, 0x51},
	.temperature = 0,
	.pos = 7
};
DS18B20 ds18b20_hot = {
	.SERIAL_NUMBER = {0x28, 0x7F, 0xF8, 0x87, 0x00, 0x00, 0x00, 0x65},
	.temperature = 0,
	.pos = 6
};

/*######################################### GENERAL FUNCTIONS #####################################*/

int ds18b20_test(UART_HandleTypeDef* uart){
	 int total = 0;
	 bool found;
	// DS18B20 ds18b20_hot[8];
	 //DS18B20 ds18b20_cold[8];
	 //extern DS18B20 ds18b20_terminal[8];
	 DS18B20 ds18b20_ROMs[] = {ds18b20_hot, ds18b20_terminal};

	 /* Initialize an array to store ROM values */
	 uint8_t devices_rom[MAX_DS18B20][N_DS18B20_SERIAL_NUMBER_BYTES];

	 /* Search and store ROM values from connected thermostats*/
	 ds18b20_search_ROM(devices_rom, uart);

	 /*Analyze collected ROM values against expected values*/
	 for(int i=0; i< MAX_DS18B20; i++){
		 for(int j=0; j<MAX_DS18B20; j++){
			 found = true;
			 for(int k=0; k<N_DS18B20_SERIAL_NUMBER_BYTES; k++){
				 if(ds18b20_ROMs[i].SERIAL_NUMBER[k] != devices_rom[j][k]){
					 found = false;
					 break;
				 }
			 }
			 if(found){
				 total++;
			 }
		 }
	 }

	 if(total == MAX_DS18B20){
		 return 0;
	 }

	 return 1;

}

/* Drive the data bus line LOW*/
void ds18b20_drive_LOW(void){
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
}

/* Release the data line -> External pull-up resistor drives the line HIGH*/
void ds18b20_release_HIGH(void){
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
}

/* Write logic 0 on the data bus*/
void ds18b20_write_0(void){
	TIMER_US_DELAY(1); // recovery time

	/* Drive the line down for 70 micro-seconds*/
	ds18b20_drive_LOW();
	TIMER_US_DELAY(100);

	/* Release the line - Pull-up resistor drives the line HIGH for 10 micro-seconds*/
	ds18b20_release_HIGH();
	TIMER_US_DELAY(10);
}

void ds18b20_write_1(void){
	TIMER_US_DELAY(1); // recovery time

	/* Drive the line down for 10 micro-seconds*/
	ds18b20_drive_LOW();
	TIMER_US_DELAY(15);

	/* Release the line - Pull-up resistor drives the line HIGH for 60 micro-seconds*/
	ds18b20_release_HIGH();
	TIMER_US_DELAY(90);
}

/* Start the communication with sensors*/
bool ds18b20_start(void){
	bool response = true;
	/* Pull the line LOW for 500 micro-seconds*/
	ds18b20_drive_LOW();
	TIMER_US_DELAY(500);
	/* Release the line*/
	ds18b20_release_HIGH();

	/* Wait for 40 micro-seconds and check response from DS18B20*/
	TIMER_US_DELAY(40);
	ds18b20_status = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);
	if (ds18b20_status != GPIO_PIN_RESET){
		response = false;
	}
	TIMER_US_DELAY(450);
	return response;
}

void ds18b20_write_byte(uint8_t command){
	for(int i=0; i< 8; i++){
		if(command & 0x01){ds18b20_write_1();}
		else{ds18b20_write_0();}
		command = (command >> 1);
	}
}

uint8_t* ds18b20_read(bool temperature_reading, int n_i, int n_j, UART_HandleTypeDef* uart){
	static uint8_t data_array[9]; // 9 bytes of data
	static uint8_t temperature_data[3];

	int i;
	for (i = 0; i<n_i; i++){
		uint8_t byte = 0x00;
		for (int j=0; j<n_j; j++){
			//TIMER_US_DELAY(1); // Recovery time

			/* Hold the line low for 15 micro-seconds*/
			ds18b20_drive_LOW();
			TIMER_US_DELAY(1);

			/* Release the line for 10 micro-seconds*/
			ds18b20_release_HIGH();
			TIMER_US_DELAY(5);

			if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN) == GPIO_PIN_SET){
				byte = (byte >> 1);
				byte = byte | 0x80;
			}
			else{
				byte = (byte >> 1);
			}
			TIMER_US_DELAY(45);
		}
		data_array[i] = byte;
		//print_hex_f_array(uart,  data_array, 5000, true, false, false, false, true);
		//print_hex_f_array(uart, data_array, 5000, true, false, false, false, true);
		//HAL_UART_Transmit(uart, data_array, 1, 1000);
	}
	data_array[i] = 0x00;

	if (temperature_reading){
		temperature_data[0] = data_array[0];
		temperature_data[1] = data_array[1];
		temperature_data[2] = 0x00;
		return temperature_data;
	}
	//print_hex_f_array(uart, data_array, 5000, true, false, false, true, true);
	return data_array;
}

char* ds18b20_read_temperature(DS18B20* sensor, bool skip_rom, UART_HandleTypeDef* uart){
	static char temperature_data[20];
	char temp_array[20];

	uint8_t* data = ds18b20_read_scratchpad(skip_rom, sensor, uart);
	int16_t raw_temp = (data[1] << 8) | data[0];
	float result;
	result = raw_temp * 0.0625;
	memset(temperature_data, 0, sizeof(temperature_data));
	/* Sign of the temperature */
	temperature_data[0] = (result < 0)? '-': '+';
	temperature_data[1] = '\0';

	/* Integer number of the temperature */
	sprintf(temp_array, "%d.", abs((int)result));
	strcat(temperature_data, temp_array);
	//end_null[0] = '.';

	/* Floating part of the temperature */
	sprintf(temp_array, "%03d °C", (int)((fabs(result - (int)result)) * 1000));
	strcat(temperature_data, temp_array);

	return temperature_data;
}

float ds18b20_get_temperature(DS18B20* sensor, bool skip_rom, UART_HandleTypeDef* uart){
	float result = -1;
	while(result < 0){
		uint8_t* data = ds18b20_read_scratchpad(skip_rom, sensor, uart);

		int16_t raw_temp = (data[1] << 8) | data[0];
		result = raw_temp * 0.0625;
	}
	return result;
}
/*#############################################################################################*/

/*######################################### ROM FUNCTIONS #####################################*/
/* Look for sensors in the data BUS and read their ROM*/
int8_t ds18b20_search_ROM(uint8_t device_rom[MAX_DS18B20][N_DS18B20_SERIAL_NUMBER_BYTES], UART_HandleTypeDef* uart) {
    uint8_t current_rom[64];  // 64 bits for the current ROM
    uint8_t path[64];         // Path for conflict resolution
    int index = -1;           // Farthest conflict index
    int count = 0;            // Conflict counter
    int total = 0;            // Total number of sensors detected
    char a;
    //char msg[30] = "LEAVING IN HERE";
    memset(device_rom, 0, MAX_DS18B20 * N_DS18B20_SERIAL_NUMBER_BYTES);
    //char lop1 = 'A';
    			//HAL_UART_Transmit(uart, (uint8_t*)&lop1, 1, HAL_MAX_DELAY);
    			//HAL_Delay(10);
    do {
    	// Reset the current ROM and path
    	memset(current_rom, 0, sizeof(current_rom));
        // Start communication with sensors in the bus
        ds18b20_start();
        ds18b20_write_byte(DS18B20_SEARCH_ROM);

        // Read 64-bit serial number
        for (int i = 0; i < 64; i++) {
            // Read two bits (response) for conflict resolution
        	uint8_t* response = (ds18b20_read(false, 2, 1, uart));

            if (!response) {
                return -1; // Communication error
            }
            if (response[0] == 0x00 && response[1] == 0x80) {
                current_rom[i] = 0;
                path[i] = 0;
                a = '0';
                ds18b20_write_0();
            } else if (response[0] == 0x80 && response[1] == 0x00) {
                current_rom[i] = 1;
                path[i] = 1;
                a = '1';
                ds18b20_write_1();
            } else if (response[0] == 0 && response[1] == 0) {
                if (i == index) {
                    // Resolve conflict by toggling the path
                    path[i] ^= 1;
                    current_rom[i] = path[i];
                    count--;
                    if(path[i] == 1){ds18b20_write_1();}
                    else{ds18b20_write_0();}

                } else {
                    // New conflict
                    index = i;
                    count++;
                    path[i] = 0;
                    current_rom[i] = 0;
                    ds18b20_write_0();
                }
            } else {
                char msg[20] = "FAILD TO COMPLETE\n";
                HAL_UART_Transmit(uart, (uint8_t*)&msg, 19, HAL_MAX_DELAY);
                return -1; // Invalid response
            }
        }

        // Convert 64-bit current_rom to 8-byte device_rom[total]
        if (total < MAX_DS18B20) {
            for (int j = 0; j < N_DS18B20_SERIAL_NUMBER_BYTES; j++) {
            	device_rom[total][j] = (current_rom[j * 8 + 7] << 7) |
									   (current_rom[j * 8 + 6] << 6) |
									   (current_rom[j * 8 + 5] << 5) |
									   (current_rom[j * 8 + 4] << 4) |
									   (current_rom[j * 8 + 3] << 3) |
									   (current_rom[j * 8 + 2] << 2) |
									   (current_rom[j * 8 + 1] << 1) |
									   (current_rom[j * 8 + 0] << 0);

					}
            total++;
        } else {
            a = 'L';
            HAL_UART_Transmit(uart, (uint8_t*)&a, 1, HAL_MAX_DELAY);
            return -2; // Exceeded MAX_SENSORS
        }

    } while (count != 0); // Continue until all conflicts are resolved

    return total; // Return the total number of sensors detected
}
/* Read ROM from a specific Sensor*/
uint8_t* ds18b20_read_ROM(UART_HandleTypeDef* uart){
	/* Start communication*/
	ds18b20_start();
	ds18b20_write_byte(DS18B20_READ_ROM);
	return ds18b20_read(false, 8, 8, uart);
}
/* Match a 64bits serial number of a sensor */
void ds18b20_match_ROM(DS18B20* sensor){
	ds18b20_write_byte(DS18B20_MATCH_ROM);
	for(int i=0; i<8;i++){
		ds18b20_write_byte(sensor->SERIAL_NUMBER[i]);
	}
}
/* Skip ROM and send commands - only used if there is only one sensor in the line */
void ds18b20_skip_ROM(){
	ds18b20_write_byte(DS18B20_SKIP_ROM);
}
/* Search if any of the sensors in the line had the alarm triggered*/
void ds18b20_alarm_search(){
	ds18b20_write_byte(DS18B20_ALARM_SEARCH);
}

										/********** FUNCTION COMMANDS **********/
/* Starts the process to convert temperature at the sensor*/
void ds18b20_convert_T(){
	ds18b20_write_byte(DS18B20_CONVERT_T);
}

/* Write some data in the sensor */
void ds18b20_write_scratchpad(){
	ds18b20_write_byte(DS18B20_WRITE_SCRATCHPAD);
}

/* Read data from the sensor - (temperature is within this data) */
uint8_t* ds18b20_read_scratchpad(bool skip_rom, DS18B20* sensor, UART_HandleTypeDef* uart){
	/* Start communication*/
	ds18b20_start();

	/* Target the sensor to read from */
	if(skip_rom){ds18b20_skip_ROM();}
	else{ds18b20_match_ROM(sensor);}

	/* Start conversion procedure in the DS18B20 and wait for 200 mili-seconds for conversion */
	ds18b20_convert_T();
	HAL_Delay(200);

	/* Restart communication*/
	ds18b20_start();
	if(skip_rom){ds18b20_skip_ROM();}
	else{ds18b20_match_ROM( sensor);}
	ds18b20_write_byte(DS18B20_READ_SCRATCHPAD);
	/* TRUE -> specifies that it is reading temperature*/
	return ds18b20_read(skip_rom, 9, 8, uart);
}

void ds18b20_run(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Start_IT(htim);
}

void ds18b20_idle(TIM_HandleTypeDef *htim){

}






