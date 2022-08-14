/*
 * led.h
 *
 *  Created on: Aug 13, 2022
 *      Author: frag
 */

#ifndef LED_H_
#define LED_H_

#include "hw_def.h"

#ifdef _USE_HW_LED

#define LED_MAX_CH		HW_LED_MAX_CH

bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToogle(uint8_t ch);

#endif

#endif /* LED_H_ */
