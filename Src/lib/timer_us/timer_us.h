/*
 * timer_us.h
 *
 *  Created on: Jan 13, 2025
 *      Author: lucas
 */

#ifndef SRC_LIB_TIMER_US_TIMER_US_H_
#define SRC_LIB_TIMER_US_TIMER_US_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

extern TIM_HandleTypeDef Tim_Def;

void TIMER_US_INIT(void);
void TIMER_US_DELAY(uint16_t time);

#endif /* SRC_LIB_TIMER_US_TIMER_US_H_ */
