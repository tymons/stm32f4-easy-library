/*
 * rtc.c
 *
 *  Created on: 04.04.2019
 *      Author: Tymoteusz Cejrowski
 */
#include "stm32f407xx.h"

/**
 * @brief	Constructor
 *
 * @param	source	- 	enum for clock input type. It can be:
 * 						RTC_SOURCE_LSI, for internal 32 kHz oscillator
 * 						RTC_SOURCE_LSE, for external 32768 Hz crystal (not implemented)
 * 						RTC_SOURCE_HSE, for internal HSE divided by prescaller
 * @return	RTC_t	-	object for RTC clock
 */
RTC_t _Rtc(RTC_source_e source)
{
	RCC->BDCR |= RCC_BDCR_BDRST;								// Reset backup domain
	RCC->BDCR |= ((uint8_t) source) << RCC_BDCR_RTCSEL_Pos; 	// Initialize clock input

	if(source == RTC_SOURCE_LSE) {
		RCC->BDCR |= RCC_BDCR_LSEON;							// Enable LSE clock
		while(!(RCC->BDCR & RCC_BDCR_LSERDY));					// Wait for LSE stable state
	} else if(source == RTC_SOURCE_HSE) {
		//TODO: implement
	}

	RCC->BDCR |= RCC_BDCR_RTCEN;	// RTC Clock enable
}
