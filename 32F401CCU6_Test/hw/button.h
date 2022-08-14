/*
 * button.h
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "hw_def.h"

#ifdef _USE_HW_BUTTON

#define BUTTON_MAX_CH		HW_BUTTON_MAX_CH

bool buttonInit(void);
GPIO_PinState buttonGet(uint8_t ch);

#endif

#endif /* BUTTON_H_ */
