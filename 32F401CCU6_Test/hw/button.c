/*
 * button.c
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */

#include "button.h"

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t      pin;
	GPIO_PinState on_state;
}button_tbl_t;

button_tbl_t button_tbl[BUTTON_MAX_CH] =
{
		{UKEY_GPIO_Port, UKEY_Pin, GPIO_PIN_RESET},
};


bool buttonInit(void)
{
	bool ret=true;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = UKEY_Pin;

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(UKEY_GPIO_Port, &GPIO_InitStruct);

	for (int i=0; i<BUTTON_MAX_CH; i++)
	{
		GPIO_InitStruct.Pin = button_tbl[i].pin;
		HAL_GPIO_Init(button_tbl[i].port, &GPIO_InitStruct);
	}

	return ret;
}

GPIO_PinState buttonGet(uint8_t ch)
{
	GPIO_PinState btn = GPIO_PIN_RESET;

	if( HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin) == button_tbl[ch].on_state)
	{
		btn = GPIO_PIN_SET;
	}

	return btn;
}
