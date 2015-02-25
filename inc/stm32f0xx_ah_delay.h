/**
 ******************************************************************************
 * @file    stm32f0xx_ah_delay.h
 * @author  Alen Helac
 * @version V1.0.0
 * @date    24-February-2015
 * @brief   Simple delay functionality (busy waiting, using SysTick) header file.
 * 			Depends on RCC component(stm32f0xx_rcc.h)
 ******************************************************************************
 */

#ifndef INC_STM32F0XX_AH_DELAY_H
#define INC_STM32F0XX_AH_DELAY_H

#include <stdbool.h>
#include "stm32f0xx_rcc.h"

/**
 *  @brief Global variable used to count milliseconds from the beginning of delay
 */
volatile extern uint32_t AH_DELAY_Milliseconds;

/**
 * @brief Global variable used to indicate if one delay function is in process
 */
volatile extern bool AH_DELAY_In_Process;

/**
 * @brief  Defines SysTick_Handler interrupt service routine to increment milliseconds
 *         counter if delay is enabled (in progress)
 * @return void
 */
void SysTick_Handler(void);

/**
 * @brief  Initiates SysTick to fire interrupt every 1ms
 * @return void
 */
void AH_DELAY_SysTickInit(void);

/**
 * @brief Implements busy wait loop to make specified delay
 * @param uint32_t: delay in milliseconds
 * @return void
 */
void AH_DELAY_DelayMs(uint32_t delayMs);

#endif /* __STM32F0XX_AH_DELAY_H */
