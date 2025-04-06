/*
 * temperature_control.c
 *
 *  Created on: Jan 16, 2025
 *      Author: lucas
 */

#include "temperature_control.h"


int reach_temperature(Water *water, Valve valve){
	return 0;
}
int get_rough_position(Water *water, Valve valve){
	return (int)water->terminalWaterTemp/valve.degPerStep;
}
void update_temperature(Water *water, Valve valve){

}
uint8_t set_temperature(Water *water, float temperature, Valve valve){
	return 0;
}
void enable_temperature_control(Water *water, TIM_HandleTypeDef* timer){

}
void disable_temperature_control(Water *water, TIM_HandleTypeDef*timer){

}
