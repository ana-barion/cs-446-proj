/*
 * timer_us.c
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */
#include "main.h"

TIM_HandleTypeDef Tim_Def;

void TIMER_US_INIT(void){
	HAL_StatusTypeDef status_tim3 = HAL_OK;

	Tim_Def.Instance = TIM3;
	Tim_Def.Init.Prescaler = 79;
	Tim_Def.Init.Period = 65535;
	Tim_Def.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim_Def.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim_Def.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&Tim_Def);
    if (status_tim3 != HAL_OK) {
    	Error_Handler();
    }
}
void TIMER_US_DELAY(uint16_t time){
	HAL_TIM_Base_Start(&Tim_Def);
	uint32_t startTick = __HAL_TIM_GET_COUNTER(&Tim_Def);
	uint32_t current_time = startTick;
    while ((current_time - startTick) < time) {
        current_time = __HAL_TIM_GET_COUNTER(&Tim_Def);
    }

    HAL_TIM_Base_Stop(&Tim_Def);
    __HAL_TIM_SET_COUNTER(&Tim_Def, 0);
}
