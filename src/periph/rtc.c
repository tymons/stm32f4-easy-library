/*
 * rtc.c
 *
 *  Created on: 04.04.2019
 *      Author: Tymoteusz Cejrowski
 */
#include "stm32f407xx.h"
#include "rtc.h"

/**
 * @brief 	Function for initialization STM32F4 RTC peripherial
 *
 * @param	source	- 	enum for clock input type. It can be:
 * 						RTC_SOURCE_LSI, for internal 37 kHz oscillator (STM32F4)
 * 						RTC_SOURCE_LSE, for external 32768 Hz crystal (not implemented)
 * 						RTC_SOURCE_HSE, for internal HSE divided by prescaller
 * @return 	void
 */
void _rtc_periphInitialize(RTC_source_e source)
{
	RCC->BDCR |= RCC_BDCR_BDRST;								// Reset backup domain
	RCC->BDCR |= ((uint8_t) source) << RCC_BDCR_RTCSEL_Pos; 	// Initialize clock input

	switch (source) {
		case RTC_SOURCE_LSE:
			RCC->BDCR |= RCC_BDCR_LSEON;							// Enable LSE clock
			while(!(RCC->BDCR & RCC_BDCR_LSERDY));					// Wait for LSE stable state
			break;

		case RTC_SOURCE_LSI:
			RTC->PRER &= ~(RTC_PRER_PREDIV_A_Msk | RTC_PRER_PREDIV_S_Msk);	// Reset prescalers
			RTC->PRER |= (124 << RTC_PRER_PREDIV_A_Pos);						// Set async and sync prescalers to
			RTC->PRER |= (295 << RTC_PRER_PREDIV_S_Pos);						// obtain 1 Hz clock (Application note: AN4759)
			break;

		case RTC_SOURCE_HSE:
			// TODO: implement
			break;
	}

	RCC->BDCR |= RCC_BDCR_RTCEN;	// RTC Clock enable
}
/**
 * @brief	Constructor
 *
 * @param	source	- 	enum for clock input type. It can be:
 * 						RTC_SOURCE_LSI, for internal 37 kHz oscillator (STM32F4)
 * 						RTC_SOURCE_LSE, for external 32768 Hz crystal (not implemented)
 * 						RTC_SOURCE_HSE, for internal HSE divided by prescaller
 * @return	RTC_t	-	object for RTC clock
 */
RTC_t _Rtc(RTC_source_e source)
{
	RTC_t _rtc;

	_rtc_periphInitialize(source);

	return _rtc;
}
