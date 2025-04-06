/*
 * pumps.h
 *
 *  Created on: Jan 16, 2025
 *      Author: lucas
 */

#ifndef SRC_LIB_EQUIPMENTS_PUMPS_H_
#define SRC_LIB_EQUIPMENTS_PUMPS_H_

#define turn_back_pump_on (valve1_A__GPIO_Port->BSRR = 1U << 0);
#define turn_back_pump_off (back_pump_GPIO_Port->BSRR = 1U << (0 + 16));

#define turn_terminal_pump_on (valve1_A__GPIO_Port->BSRR = 1U << 1);
#define turn_terminal_pump_off (valve1_A__GPIO_Port->BSRR = 1U << (1 + 16));


#endif /* SRC_LIB_EQUIPMENTS_PUMPS_H_ */
