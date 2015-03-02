#include "stm32f0_ah_discovery.h"

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
