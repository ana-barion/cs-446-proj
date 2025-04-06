#include "main.h"

int VALVE_MODE_STANDBY(void){
	VALVE_M1_RST;
	VALVE_M2_RST;
	VALVE_M3_RST;
	return 0;
}

int VALVE_MODE_FULL_CW(void){
	VALVE_M1_RST;
	VALVE_M2_RST;
	VALVE_M3_SET;
	return 0;
}
int VALVE_MODE_1_2A_CW(void){
	VALVE_M1_RST;
	VALVE_M2_SET;
	VALVE_M3_RST;
	return 0;
}
int VALVE_MODE_1_2B_CW(void){
	VALVE_M1_RST;
	VALVE_M2_SET;
	VALVE_M3_SET;
	return 0;
}
int VALVE_MODE_1_4_CW(void){
	VALVE_M1_SET;
	VALVE_M2_RST;
	VALVE_M3_RST;
	return 0;
}
int VALVE_MODE_1_8_CW(void){
	VALVE_M1_SET;
	VALVE_M2_RST;
	VALVE_M3_SET;
	return 0;
}
int VALVE_MODE_1_16_CW(void){
	VALVE_M1_SET;
	VALVE_M2_SET;
	VALVE_M3_RST;
	return 0;
}

int VALVE_CONTROL_CW_STEP(uint8_t step, Valve *valve){
	HAL_Delay(1);
	VALVE_CCW_SET;
	TIMER_US_DELAY(1);
	VALVE_RST_SET;
	TIMER_US_DELAY(1);
	VALVE_EN_SET;
	TIMER_US_DELAY(1);
	VALVE_TQ_SET;
	TIMER_US_DELAY(1);

	VALVE_CLK_RST;
	for(int i=0; i<step && (valve->steps < MAX_STEPS); i++){
		VALVE_CLK_SET;
		HAL_Delay(10);
		VALVE_CLK_RST;
		HAL_Delay(10);
		valve->steps++;
	}
	return 0;
}

int VALVE_CONTROL_CCW_STEP(uint8_t step, Valve *valve){
	HAL_Delay(1);
	VALVE_CCW_RST;
	TIMER_US_DELAY(1);
	VALVE_RST_SET;
	TIMER_US_DELAY(1);
	VALVE_EN_SET;
	TIMER_US_DELAY(1);
	VALVE_TQ_SET;
	TIMER_US_DELAY(1);

	VALVE_CLK_RST;
	for(int i=0; i<(step && (valve->steps > 0)); i++){
		VALVE_CLK_SET;
		HAL_Delay(10);
		VALVE_CLK_RST;
		HAL_Delay(10);
		valve->steps--;
	}
	return 0;
}

int VALVE_CONTROL_APROX(Valve *valve){
	if(valve->aprox > valve->steps){
		VALVE_CONTROL_CW_STEP((valve->aprox - valve->steps), valve);
	}
	else if(valve->aprox < valve->steps){
		VALVE_CONTROL_CCW_STEP((valve->aprox - valve->steps), valve);
	}
}

int VALVE_CONTROL_HANDLE(Valve *valve, Button *button, DS18B20 *terminal){
	if(terminal->temperature < button->temp_set){
		VALVE_CONTROL_CW_STEP(1, valve);
	}
	else if(terminal->temperature > button->temp_set){
		VALVE_CONTROL_CCW_STEP((valve->aprox - valve->steps), valve);
	}
}















