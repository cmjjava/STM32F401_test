/*
 * hw.c
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */


#include "hw.h"

void hwInit()
{
	//bspInit();

	ledInit();
	buttonInit();
	uartInit();

	uartOpen(_DEF_UART1, 115200);
	uartOpen(_DEF_UART2, 115200);

}
