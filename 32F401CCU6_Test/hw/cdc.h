/*
 * cdc.h
 *
 *  Created on: Aug 14, 2022
 *      Author: frag
 */

#ifndef CDC_H_
#define CDC_H_

#ifdef _USE_HW_CDC

uint32_t cdcAvailable(void);
uint8_t cdcRead( void );
void cdcDataIn( uint8_t rx_data );
uint32_t cdcWrite( uint8_t *p_data, uint16_t length );
uint32_t cdcGetBaud(void);

#endif

#endif /* CDC_H_ */
