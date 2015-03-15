#ifndef INC_STM32F0_AH_RTC_H
#define INC_STM32F0_AH_RTC_H

#include "main.h"
#include <time.h>

extern RTC_TimeTypeDef RTC_TimeStructure;
extern RTC_DateTypeDef RTC_DateStructure;

extern const char* weekdayEnName[];

/**
  * @brief Initialize the RTC peripheral to use LSI oscillator with dividers
  * calculated for 40kHz.
  * @param  None
  * @retval None
  */
void AH_RTC_Init(void);

/**
 * @brief Returns true if daylight savings regime (summer time) is on, based on current RTC time
 * @return bool
 */
bool AH_RTC_IsDaylightSavingActive(void);

/**
 * @brief Calculates unix timestamp for provided date and time.
 * @param RTC_TimeTypeDef: time RTC struct
 * @param RTC_DateTypeDef: date RTC struct
 * @return time_t: unix timestamp
 */
time_t AH_RTC_GetTimestamp(RTC_TimeTypeDef ts, RTC_DateTypeDef ds);

/**
 * @brief Gets unix timestamp of moment when daylight savings should start (beginning of summer time), for provided year.
 * @param uint8_t: year, in range [0, 99]
 * @return time_t: unix timestamp
 */
time_t AH_RTC_GetDaylightSavingsStart(uint8_t year);

/**
 * @brief Gets unix timestamp of moment when daylight savings should end (beginning of winter time), for provided year.
 * @param uint8_t: year, in range [0, 99]
 * @return time_t unix timestamp
 */
time_t AH_RTC_GetDaylightSavingsEnd(uint8_t year);

/**
 * @brief This function will return RTC weekday based on date provided.
 * @param uint8_t day: day component of a date
 * @param uint8_t month: month component of a date
 * @param uint8_t year: year component of a date, in range [0,99]
 * @return uint8_t @ref RTC_WeekDay_Definitions
 */
uint8_t AH_RTC_GetWeekdayForDate(uint8_t day, uint8_t month, uint8_t year);

/**
 * @brief This function will set properties of provided time structure to time when project was built.
 * @note Build date and time is parsed in @ref datetime_build_defs.h
 * @param RTC_TimeTypeDef*: pointer to RTC time structure
 * @return void
 */
void RTC_GetBuildTime(RTC_TimeTypeDef * timeStr);

/**
 * @brief This function will set properties of provided date structure to date when project was built.
 * @note Build date and time is parsed in @ref datetime_build_defs.h
 * @param RTC_DateTypeDef*: pointer to RTC date structure
 * @return void
 */
void RTC_GetBuildDate(RTC_DateTypeDef * dateStr);

/**
 * @brief Sets RTC time and date to point in time when last build was executed.
 * @param None
 * @return bool success
 */
bool AH_RTC_SetBuildTime(void);

#endif /* INC_STM32F0_AH_RTC_H */
