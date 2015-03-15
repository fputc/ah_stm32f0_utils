/**
 ******************************************************************************
 * @file    stm32f0_ah_discovery.c
 * @author  Alen Helac
 * @version V1.0.0
 * @brief   Some functionality related to STM32F0-DISCOVERY board that can be
 * easily reused elsewhere.
 ******************************************************************************
 */

#include "stm32f0_ah_discovery.h"
#include "stm32f0xx_usart.h"

const uint16_t AH_Discovery_Led_Pin[2] = {
	LED3_GPIO_PIN,
	LED4_GPIO_PIN
};

const uint32_t AH_Discovery_Periph_Clk[2] = {
	LED3_GPIO_PERIPH_CLK,
	LED4_GPIO_PERIPH_CLK
};

GPIO_TypeDef* AH_Discovery_Led_Gpio[2] = {
	LED3_GPIO_PORT,
	LED4_GPIO_PORT
};

void AH_Discovery_Led_Init(AH_Discovery_Led_TypeDef led) {

	GPIO_InitTypeDef Gp;

	RCC_AHBPeriphClockCmd(AH_Discovery_Periph_Clk[led], ENABLE);

	Gp.GPIO_Pin = AH_Discovery_Led_Pin[led];
	Gp.GPIO_Mode = GPIO_Mode_OUT;
	Gp.GPIO_OType = GPIO_OType_PP;
	Gp.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Gp.GPIO_Speed = GPIO_Speed_Level_1;

	GPIO_Init(AH_Discovery_Led_Gpio[led], &Gp);

}

void AH_Discovery_Led_Action(AH_Discovery_Led_TypeDef led, AH_Led_Action_TypeDef action) {

	switch (action) {
		case AH_Led_Action_On:
			GPIO_SetBits(AH_Discovery_Led_Gpio[led], AH_Discovery_Led_Pin[led]);
			break;
		case AH_Led_Action_Off:
			GPIO_ResetBits(AH_Discovery_Led_Gpio[led], AH_Discovery_Led_Pin[led]);
			break;
		case AH_Led_Action_Toggle:
			if (GPIO_ReadInputDataBit(AH_Discovery_Led_Gpio[led], AH_Discovery_Led_Pin[led])) {
				AH_Discovery_Led_Action(led, AH_Led_Action_Off);
			}
			else {
				AH_Discovery_Led_Action(led, AH_Led_Action_On);
			}
			break;
	}
}

void AH_Discovery_Push_Button_Init() {

	GPIO_InitTypeDef Gp;

	RCC_AHBPeriphClockCmd(AH_DISCOVERY_BUTTON_CLK, ENABLE);

	Gp.GPIO_Pin = AH_DISCOVERY_BUTTON_PIN;
	Gp.GPIO_Mode = GPIO_Mode_IN;
	Gp.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(AH_DISCOVERY_BUTTON_PORT, &Gp);
}

bool AH_Discovery_Is_Button_Pushed() {
	return (bool) GPIO_ReadInputDataBit(AH_DISCOVERY_BUTTON_PORT, AH_DISCOVERY_BUTTON_PIN);
}

void AH_Discovery_Debug_Init(int baudRate) {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1,ENABLE);
}

void PrintChar(char c)
{
	  USART_SendData(USART1, (uint8_t) c);

	  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	  {}
}
