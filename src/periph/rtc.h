/*
 * rtc.h
 *
 *  Created on: 04.04.2019
 *      Author: Tymoteusz Cejrowski
 */

#ifndef PERIPH_RTC_H_
#define PERIPH_RTC_H_

#include <stddef.h>

typedef enum {
	RTC_SOURCE_LSE = 0b00000001,
	RTC_SOURCE_LSI = 0b00000010,
	RTC_SOURCE_HSE = 0b00000011,
}RTC_source_e;

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t week_day;
	uint8_t month_day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint32_t milisecond;
}RTC_date_t;

typedef struct RTC_t RTC_t;
struct RTC_t{

	void(*set_current_date_by_timestamp)(uint32_t timestamp);
	void(*set_current_date)(RTC_date_t date_time);
	void(*set_alarm_a)(void);
	void(*set_alarm_b)(void);
};

// Constructor
RTC_t _Rtc(RTC_source_e source);

#endif /* PERIPH_RTC_H_ */
