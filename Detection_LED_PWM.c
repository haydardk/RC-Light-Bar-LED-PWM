/*
 * Detection_LED_PWM.c
 *
 *  Created on: Jul 6, 2024
 *      Author: CASPER
 */

#include "Detection_LED_PWM.h"

#include "stm32f4xx_hal.h"

// #define LED_FLASH_ADDR  0x08060000 //SONDAN BAŞLIYORUZ

int LED_MOD;
uint32_t MOD_DATA;

void Detection_LED_Init(void){

	TIM2->PSC = 88 - 1 ; // (CLOCK sinyali 8MHz)/88 = 90909 Hz -> Timer Clock
	TIM2->ARR = 1000 -1  ; // Timer Clock / (ARR+1) = 90.909Hz PWM frekansı
	// TIM2->CCR1 = 100 ; //%10 Duty
	//Duty Cycle %10-%17
	/* Mod1 Kapalı                Sadece KAPALI ve Yavaş Disko kullanılacak
	   Mod2 Sabit Açık            Sisteme RESET atıldığında MOD2'den başlar
	   Mod3 Yavaş Disko
	   Mod4 Hızlı Disko
	*/
	// PWM Düzenlemeleri
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

	TIM2->CCER |= TIM_CCER_CC1E;
}
void Detection_LED_Enable(void)
{
	TIM2->CR1 |= TIM_CR1_CEN;
	TIM2->EGR |= TIM_EGR_UG;
}

void Detection_LED_Disable(void)
{
	TIM2->CR1 &= ~(TIM_CR1_CEN);
}
void Detection_LED_Set ( int value){
	if (value == 0){
		TIM2->CCR1 = 0 ;
	}
	if (value == 1){
		TIM2->CCR1 = 105;
		LED_MOD++;
	}
	if (value == 2){
		TIM2->CCR1 = 170;
		LED_MOD++;
	}
}
void LED_Mod_Detection(void){
	if(LED_MOD%4 == 0){
		LED_MOD = MOD_OFF ;
	}
	if(LED_MOD%4 == 1){
		LED_MOD = MOD_FIXED ;
	}
	if(LED_MOD%4 == 2){
		LED_MOD = MOD_SLOW ;
	}
	if(LED_MOD%4 == 3){
		LED_MOD = MOD_RAPID ;
	}
	MOD_DATA = LED_MOD;
}

void Switch_Mode(int value){
	if (value==0 && MOD_DATA==3){
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
	}
	if (value==0 && MOD_DATA==2){
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
	}
	if (value==0 && MOD_DATA==1){
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
		Detection_LED_Set(2);
		HAL_Delay(10);
		Detection_LED_Set(1);
		HAL_Delay(10);
	}
}

/* void LED_MOD_Save(uint32_t Address , uint32_t MOD_DATA ){
	// 0x08060000
	HAL_StatusTypeDef status;
	uint32_t PageError = 0;
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef eraseInitStruct;
	eraseInitStruct.TypeErase = TYPEERASE_SECTORS;
	eraseInitStruct.Sector = FLASH_SECTOR_7; // Örnek olarak 7. sektör
	eraseInitStruct.NbSectors = 1;
	eraseInitStruct.VoltageRange = VOLTAGE_RANGE_3;

	status = HAL_FLASHEx_Erase(&eraseInitStruct, &PageError);
	status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, MOD_DATA);

	HAL_FLASH_Lock();
}
uint32_t LED_MOD_Remember(void){
	return *(__IO uint32_t*)LED_FLASH_ADDR;
}
*/
