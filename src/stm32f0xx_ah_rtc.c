#include "stm32f0xx_ah_rtc.h"

RTC_TimeTypeDef RTC_TimeStructure;
RTC_DateTypeDef RTC_DateStructure;

/**
 * @brief Returns true if daylight savings regime (summer time) is on, based on current RTC time
 * @return bool
 */
bool AH_RTC_IsDaylightSavingActive(void) {
	time_t dsStart;
	time_t dsEnd;
	time_t now;

	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

	dsStart = AH_RTC_GetDaylightSavingsStart(RTC_DateStructure.RTC_Year);
	dsEnd = AH_RTC_GetDaylightSavingsEnd(RTC_DateStructure.RTC_Year);
	now = AH_RTC_GetTimestamp(RTC_TimeStructure,RTC_DateStructure);

	if ( now > dsStart && now <= dsEnd ) {
		return true;
	}
	return false;
}

/**
 * @brief Calculates unix timestamp for provided date and time.
 * @param RTC_TimeTypeDef: time RTC struct
 * @param RTC_DateTypeDef: date RTC struct
 * @return time_t: unix timestamp
 */
time_t AH_RTC_GetTimestamp(RTC_TimeTypeDef ts, RTC_DateTypeDef ds) {
	struct tm calendar;
	calendar.tm_hour = ts.RTC_Hours;
	calendar.tm_min = ts.RTC_Minutes;
	calendar.tm_sec = ts.RTC_Seconds;
	calendar.tm_mday = ds.RTC_Date;
	calendar.tm_mon = ds.RTC_Month - 1; // tm_mon range [0,11] ; RTC_Month range [1,12]
	calendar.tm_year = 100 + ds.RTC_Year; // tm_year, since 1990 ; RTC_Year since 2000
	return mktime(&calendar);
}

/**
 * @brief Gets unix timestamp of moment when daylight savings should start (beginning of summer time), for provided year.
 * @param uint8_t: year, in range [0, 99]
 * @return time_t: unix timestamp
 */
time_t AH_RTC_GetDaylightSavingsStart(uint8_t year) {
	struct tm calendar;
	uint8_t weekday = AH_RTC_GetWeekdayForDate(25, 3, year);
	uint8_t dsDay = 25 + (7 - weekday); // 25th + days until Sunday. This is the date when daylight savings start should occur

	calendar.tm_hour = 1;
	calendar.tm_min = 59;
	calendar.tm_sec = 59;
	calendar.tm_mday = dsDay;
	calendar.tm_mon = 3 - 1; // tm_mon range is [0,11]
	calendar.tm_year = 100 + year; // tm_year, since 1990; param since 2000
	return mktime(&calendar);
}

/**
 * @brief Gets unix timestamp of moment when daylight savings should end (beginning of winter time), for provided year.
 * @param uint8_t: year, in range [0, 99]
 * @return time_t unix timestamp
 */
time_t AH_RTC_GetDaylightSavingsEnd(uint8_t year) {
	struct tm calendar;
	uint8_t weekday = AH_RTC_GetWeekdayForDate(25, 10, year);
	uint8_t dsDay = 25 + (7 - weekday); // 25th + days until Sunday. This is the date when daylight savings end should occur

	calendar.tm_hour = 2;
	calendar.tm_min = 59;
	calendar.tm_sec = 59;
	calendar.tm_mday = dsDay;
	calendar.tm_mon = 10 - 1; // tm_mon range is [0,11]
	calendar.tm_year = 100 + year; // tm_year, since 1990; param since 2000
	return mktime(&calendar);
}

/**
 * @brief This function will return RTC weekday based on date provided.
 * @param uint8_t day: day component of a date
 * @param uint8_t month: month component of a date
 * @param uint8_t year: year component of a date, in range [0,99]
 * @return uint8_t @ref RTC_WeekDay_Definitions
 */
uint8_t AH_RTC_GetWeekdayForDate(uint8_t day, uint8_t month, uint8_t year) {
	uint8_t weekdays[7] = {
		RTC_Weekday_Monday,
		RTC_Weekday_Tuesday,
		RTC_Weekday_Wednesday,
		RTC_Weekday_Thursday,
		RTC_Weekday_Friday,
		RTC_Weekday_Saturday,
		RTC_Weekday_Sunday,
	};
	uint8_t index = ( day                                              	\
		+ ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) 		\
		+ (365 * (year + 4800 - ((14 - month) / 12)))              		\
		+ ((year + 4800 - ((14 - month) / 12)) / 4)                		\
		- ((year + 4800 - ((14 - month) / 12)) / 100)              		\
		+ ((year + 4800 - ((14 - month) / 12)) / 400)              		\
		- 32045                                                    		\
	) % 7;
	return weekdays[index];
}
/**
 * @brief This function will set properties of provided time structure to time when project was built.
 * @note Build date and time is parsed in @ref datetime_build_defs.h
 * @param RTC_TimeTypeDef*: pointer to RTC time structure
 * @return void
 */
void RTC_GetBuildTime(RTC_TimeTypeDef * timeStr) {

	char smin[] = {
		BUILD_MIN_CH0,
		BUILD_MIN_CH1,
		'\0'
	};

	char shr[] = {
		BUILD_HOUR_CH0,
		BUILD_HOUR_CH1,
		'\0'
	};

	char ssec[] = {
		BUILD_SEC_CH0,
		BUILD_SEC_CH1,
		'\0'
	};

	uint8_t minutes = atoi(smin);
	uint8_t hours = atoi(shr);
	uint8_t seconds = atoi(ssec);

	timeStr->RTC_H12 = RTC_H12_AM;
	/*
	timeStr->RTC_Hours = hours;
	timeStr->RTC_Minutes = minutes;
	timeStr->RTC_Seconds = seconds;
	*/
	timeStr->RTC_Hours = 1;
	timeStr->RTC_Minutes = 59;
	timeStr->RTC_Seconds = 55;
}

/**
 * @brief This function will set properties of provided date structure to date when project was built.
 * @note Build date and time is parsed in @ref datetime_build_defs.h
 * @param RTC_DateTypeDef*: pointer to RTC date structure
 * @return void
 */
void RTC_GetBuildDate(RTC_DateTypeDef * dateStr) {

	char sdate[] = {
			BUILD_DAY_CH0,
			BUILD_DAY_CH1,
			'\0'
		};

	char smonth[] = {
		BUILD_MONTH_CH0,
		BUILD_MONTH_CH1,
		'\0'
	};

	char syear[] = {
		BUILD_YEAR_CH2,
		BUILD_YEAR_CH3,
		'\0'
	};

	uint8_t date = atoi(sdate);
	uint8_t month = atoi(smonth);
	uint8_t year = atoi(syear);
	/*
	dateStr->RTC_Date = date;
	dateStr->RTC_Month = month;
	dateStr->RTC_Year = year;
	dateStr->RTC_WeekDay = AH_RTC_GetWeekdayForDate(date, month, year);
	*/

	dateStr->RTC_Date = 29;
	dateStr->RTC_Month = 3;
	dateStr->RTC_Year = 15;
	//dateStr->RTC_WeekDay = AH_RTC_GetWeekdayForDate(date, month, year);
}
