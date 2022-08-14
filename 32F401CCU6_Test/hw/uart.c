/*
 * uart.c
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */

#include "hw.h"

extern uint32_t cdcAvailable(void);
extern uint8_t cdcRead( void );
extern void cdcDataIn( uint8_t rx_data );
extern uint32_t cdcWrite( uint8_t *p_data, uint16_t length );
extern uint32_t cdcGetBaud(void);

static bool is_open[UART_MAX_CH];

bool uartInit(void)
{
	for( int i=0; i<UART_MAX_CH; i++)
	{
		is_open[i] = false;
	}

	return true;
}

bool uartOpen( uint8_t ch, uint32_t baud)
{
	bool ret = false;

	switch(ch)
	{
	case _DEF_UART1 :
		is_open[ch] = true;
		ret = true;
		break;
	}

	return ret;
}

uint32_t uartAvailable( uint8_t ch )
{
	bool ret = false;

	switch(ch)
	{
	case _DEF_UART1 :
		ret = cdcAvailable();
		break;
	}

	return ret;
}

uint8_t  uartRead(uint8_t ch)
{
	bool ret = 0;

	switch(ch)
	{
	case _DEF_UART1 :
		ret = cdcRead();
		break;
	}

	return ret;
}

uint32_t uartWrite( uint8_t ch, uint8_t *p_data, uint32_t length)
{
	bool ret = false;

	switch(ch)
	{
	case _DEF_UART1 :
		ret = cdcWrite(p_data, length);
		break;
	}

	return ret;
}

uint32_t uartPrintf( uint8_t ch, char *fmt, ...)
{
	char buf[256];
	va_list args;
	int len;
	uint32_t ret;

	va_start(args, fmt);
	len = vsnprintf(buf, 256, fmt, args);

	ret = uartWrite(ch, (uint8_t *)buf, len);

	va_end(args);

	return ret;
}

uint32_t uartGetBaud( uint8_t ch )
{
	uint32_t ret = 0;

	switch( ch )
	{
	case _DEF_UART1 :
		ret = cdcGetBaud();
		break;
	}

	return ret;
}
