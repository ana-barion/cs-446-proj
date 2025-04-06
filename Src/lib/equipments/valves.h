/*
 * valves.h
 *
 *  Created on: Jan 16, 2025
 *      Author: lucas
 */
#include "main.h"
#include "screen.h"
#ifndef SRC_LIB_EQUIPMENTS_VALVES_H_
#define SRC_LIB_EQUIPMENTS_VALVES_H_

#define feed_cold_water (valve1_A__GPIO_Port->BSRR = 1U << 3);
#define return_cold_water (valve1_A__GPIO_Port->BSRR = 1U << (3 + 16));

#define feed_hot_water (valve1_A__GPIO_Port->BSRR = 1U << 2);
#define return_hot_water (valve1_A__GPIO_Port->BSRR = 1U << (2 + 16));

/*Excitation Mode GPIOs*/
#define VALVE_M1_SET (Valve_M1_GPIO_Port->BSRR = 1U << 0)
#define VALVE_M2_SET (Valve_M2_GPIO_Port->BSRR = 1U << 1)
#define VALVE_M3_SET (Valve_M3_GPIO_Port->BSRR = 1U << 2)
#define VALVE_EN_SET (Valve_CCW_GPIO_Port->BSRR = 1U << 3)
#define VALVE_RST_SET (Valve_RST_GPIO_Port->BSRR = 1U << 4)
#define VALVE_CLK_SET (Valve_CLK_GPIO_Port->BSRR = 1U << 5)
#define VALVE_CCW_SET (Valve_CCW_GPIO_Port->BSRR = 1U << 6)
#define VALVE_LATCH_SET (Valve_LATCH_GPIO_Port->BSRR = 1U << 7)
#define VALVE_TQ_SET (Valve_TQ_GPIO_Port->BSRR = 1U << 8)
#define VALVE_M0_SET (Valve_M0_GPIO_Port->BSRR = 1U << 9)
#define VALVE_ALERT_SET (Valve_ALERT_GPIO_Port->BSRR = 1U << 10)


#define VALVE_M1_RST (Valve_M1_GPIO_Port->BSRR = 1U << 16)
#define VALVE_M2_RST (Valve_M2_GPIO_Port->BSRR = 1U << (1 + 16))
#define VALVE_M3_RST (Valve_M3_GPIO_Port->BSRR = 1U << (2 + 16))
#define VALVE_EN_RST (Valve_CCW_GPIO_Port->BSRR = 1U << (3 + 16))
#define VALVE_RST_RST (Valve_RST_GPIO_Port->BSRR = 1U << (4 + 16))
#define VALVE_CLK_RST (Valve_CLK_GPIO_Port->BSRR = 1U << (5 + 16))
#define VALVE_CCW_RST (Valve_CCW_GPIO_Port->BSRR = 1U << (6 + 16))
#define VALVE_LATCH_RST (Valve_LATCH_GPIO_Port->BSRR = 1U << (7 + 16))
#define VALVE_TQ_RST (Valve_TQ_GPIO_Port->BSRR = 1U << (8 + 16))
#define VALVE_M0_RST (Valve_M0_GPIO_Port->BSRR = 1U << (9 + 16))
#define VALVE_ALERT_RST (Valve_ALERT_GPIO_Port->BSRR = 1U << (10 + 16))

#define MAX_STEPS 100
typedef struct{
	uint8_t steps;
	uint8_t current_steps;
	uint8_t aprox;
	float degPerStep;
}Valve;
/*EXCITATION MODE*/
int VALVE_MODE_STANDBY(void);
int VALVE_MODE_FULL_CW(void);
int VALVE_MODE_1_2A_CW(void);
int VALVE_MODE_1_2B_CW(void);
int VALVE_MODE_1_4_CW(void);
int VALVE_MODE_1_8_CW(void);
int VALVE_MODE_1_16_CW(void);

/*CONTROL*/
int VALVE_CONTROL_CW_STEP(uint8_t step, Valve *valve);
int VALVE_CONTROL_CCW_STEP(uint8_t step, Valve *valve);
int VALVE_CONTROL_APROX(Valve *valve);
int VALVE_CONTROL_CLOSE(Valve *steps);
int VALVE_CONTROL_HANDLE(Valve *valve, Button *button, DS18B20 *terminal);


#endif /* SRC_LIB_EQUIPMENTS_VALVES_H_ */
