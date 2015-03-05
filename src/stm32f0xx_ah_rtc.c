#include "stm32f0_ah_rtc.h"

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
