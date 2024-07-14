/*
 * Detection_LED_PWM.h
 *
 *  Created on: Jul 6, 2024
 *      Author: CASPER
 */

#ifndef INC_DETECTION_LED_PWM_H_
#define INC_DETECTION_LED_PWM_H_

#define FLASH_LED_MOD_ADDR    0x08060000

#include "stdint.h"

typedef enum LED_MODS{
	MOD_OFF = 0,
	MOD_FIXED = 1,
	MOD_SLOW = 2,
	MOD_RAPID = 3,
}LED_MODS_e;

void Detection_LED_Init(void);
void Detection_LED_Enable(void);
void Detection_LED_Disable(void);
void Detection_LED_Set ( int value);
void LED_Mod_Detection(void);
void LED_MOD_Save(uint32_t Address , uint32_t MOD_DATA );
uint32_t LED_MOD_Remember(void);
void Switch_Mode(int value);




#endif /* INC_DETECTION_LED_PWM_H_ */
