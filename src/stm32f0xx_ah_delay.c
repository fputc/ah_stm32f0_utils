/**
  ******************************************************************************
  * @file    stm32f0xx_ah_delay.c
  * @author  Alen Helac
  * @version V1.0.0
  * @date    24-February-2015
  * @brief   Simple delay functionality (busy waiting, using SysTick) implementation file
  ******************************************************************************
  */

#include "stm32f0xx_ah_delay.h"

/**
 *  @brief Global variable used to count milliseconds from the beginning of delay
 */
volatile uint32_t AH_DELAY_Milliseconds = 0;

/**
 * @brief Global variable used to indicate if one delay function is in process
 */
volatile bool AH_DELAY_In_Process = false;

/**
 * @brief  Defines SysTick_Handler interrupt service routine to increment milliseconds
 *         counter if delay is enabled (in progress)
 * @return void
 */
void SysTick_Handler(void){
	if (AH_DELAY_In_Process) {
		AH_DELAY_Milliseconds++;
	}
}

/**
 * @brief  Initiates SysTick to fire interrupt every 1ms
 * @return void
 */
void AH_DELAY_SysTickInit(void) {
	SysTick_Config(SystemCoreClock/1000);
}

/**
 * @brief Implements busy wait loop to make specified delay
 * @param uint32_t: delay in milliseconds
 * @return void
 */
void AH_DELAY_DelayMs(uint32_t delayMs) {

	volatile uint32_t msStart;
	AH_DELAY_Milliseconds = 0;
	msStart = AH_DELAY_Milliseconds;
	AH_DELAY_In_Process = true;

	while((AH_DELAY_Milliseconds - msStart) < delayMs) {
		asm volatile("nop");
	}

	AH_DELAY_In_Process = false;
}

void AH_DELAY_StartTick(void) {
	AH_DELAY_Milliseconds = 0;
	AH_DELAY_In_Process = true;
}

void AH_DELAY_StopTick(void) {
	AH_DELAY_In_Process = false;
}

uint32_t AH_DELAY_GetTickTime(void) {
	return AH_DELAY_Milliseconds;
}

