/*
 * uart.c
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */

#include "hw.h"
#include "cdc.h"
#include "qbuffer.h"


UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

static bool is_open[UART_MAX_CH];

static qbuffer_t qbuffer[UART_MAX_CH];
static uint8_t rx_buf[256];



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
	case _DEF_UART2 :
		huart1.Instance = USART1;
		huart1.Init.BaudRate = baud;
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		huart1.Init.StopBits = UART_STOPBITS_1;
		huart1.Init.Parity = UART_PARITY_NONE;
		huart1.Init.Mode = UART_MODE_TX_RX;
		huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart1.Init.OverSampling = UART_OVERSAMPLING_16;

		HAL_UART_DeInit(&huart1);

		qbufferCreate(&qbuffer[ch], &rx_buf[0], 256);

		__HAL_RCC_DMA2_CLK_ENABLE();
		HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

		if (HAL_UART_Init(&huart1) != HAL_OK)
		{
			ret = false;
		}
		else
		{
			//qbufferCreate(&qbuffer[_DEF_UART2], &rx_buf[0], 256);
			ret = true;
			is_open[ch] = true;

			if(HAL_UART_Receive_DMA(&huart1, (uint8_t *)&rx_buf[0], 256) != HAL_OK)
			{
				ret = false;
			}

			qbuffer[ch].in  = qbuffer[ch].len - hdma_usart1_rx.Instance->NDTR;
			qbuffer[ch].out = qbuffer[ch].in;
		}
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
		case _DEF_UART2 :
			qbuffer[ch].in = (qbuffer[ch].len - hdma_usart1_rx.Instance->NDTR);
			//hdma_usart1_rx.Instance->NDTR;
			ret = qbufferAvailable(&qbuffer[ch]);
			break;
	}

	return ret;
}

uint8_t  uartRead(uint8_t ch)
{
	uint8_t ret = 0;

	switch(ch)
	{
		case _DEF_UART1 :
			ret = cdcRead();
			break;
		case _DEF_UART2:
			qbufferRead(&qbuffer[ch], &ret, 1);
			break;
	}

	return ret;
}

uint32_t uartWrite( uint8_t ch, uint8_t *p_data, uint32_t length)
{
	bool ret = false;
	HAL_StatusTypeDef status;

	switch(ch)
	{
	case _DEF_UART1 :
		ret = cdcWrite(p_data, length);
		break;
	case _DEF_UART2 :
		status = HAL_UART_Transmit(&huart1, p_data, length, 100);
		if( status == HAL_OK)
		{
			ret = length;
		}
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
