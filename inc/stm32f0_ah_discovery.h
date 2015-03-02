
#ifndef INC_STM32F0_AH_DISCOVERY_H
#define INC_STM32F0_AH_DISCOVERY_H

#include <stdbool.h>
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"

extern const uint16_t AH_Discovery_Led_Pin[2];
extern const uint32_t AH_Discovery_Periph_Clk[2];
extern GPIO_TypeDef* AH_Discovery_Led_Gpio[2];

#define AH_DISCOVERY_BUTTON_CLK RCC_AHBPeriph_GPIOA
#define AH_DISCOVERY_BUTTON_PORT GPIOA
#define AH_DISCOVERY_BUTTON_PIN GPIO_Pin_0

#define LED3_GPIO_PORT GPIOC
#define LED3_GPIO_PIN GPIO_Pin_9
#define LED3_GPIO_PERIPH_CLK RCC_AHBPeriph_GPIOC

#define LED4_GPIO_PORT GPIOC
#define LED4_GPIO_PIN GPIO_Pin_8
#define LED4_GPIO_PERIPH_CLK RCC_AHBPeriph_GPIOC

typedef enum
{
	AH_Discovery_Led3,
	AH_Discovery_Led4,
}AH_Discovery_Led_TypeDef;


typedef enum
{
	AH_Led_Action_On,
	AH_Led_Action_Off,
	AH_Led_Action_Toggle,
}AH_Led_Action_TypeDef;

void AH_Discovery_Push_Button_Init();
void AH_Discovery_Led_Init(AH_Discovery_Led_TypeDef led);
void AH_Discovery_Led_Action(AH_Discovery_Led_TypeDef led, AH_Led_Action_TypeDef action);
bool AH_Discovery_Is_Button_Pushed();

void AH_Discovery_Debug_Init(int baudRate);

/**
 * @brief  Transmit a char, if you want to use printf(),
 *         you need implement this function
 *
 * @param  pStr	Storage string.
 * @param  c    Character to write.
 */


void PrintChar(char c);

#endif /* __STM32F0_AH_DISCOVERY_H */
