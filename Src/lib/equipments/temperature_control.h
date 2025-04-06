/*
 * temperature_control.h
 *
 *  Created on: Jan 16, 2025
 *      Author: lucas
 */

#ifndef SRC_LIB_EQUIPMENTS_TEMPERATURE_CONTROL_H_
#define SRC_LIB_EQUIPMENTS_TEMPERATURE_CONTROL_H_

#include "main.h"
#include "valves.h"

typedef struct{
	float hotWaterTemp;
	float coldWaterTemp;
	float terminalWaterTemp;
}Water;

int reach_temperature(Water *water, Valve valve);
int get_rough_position(Water *water, Valve valve);
void update_temperature(Water *water, Valve valve);
uint8_t set_temperature(Water *water, float temperature, Valve valve);
void enable_temperature_control(Water *water, TIM_HandleTypeDef* timer);
void disable_temperature_control(Water *water, TIM_HandleTypeDef*timer);

#endif /* SRC_LIB_EQUIPMENTS_TEMPERATURE_CONTROL_H_ */
