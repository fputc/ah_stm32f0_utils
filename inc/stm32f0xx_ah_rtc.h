#ifndef INC_STM32F0_AH_RTC_H
#define INC_STM32F0_AH_RTC_H

/**
 * @brief Returns true if daylight savings regime (summer time) is on, based on current RTC time
 * @return bool
 */
bool AH_RTC_IsDaylightSavingActive(void);

#endif /* __STM32F0_AH_RTC_H */
