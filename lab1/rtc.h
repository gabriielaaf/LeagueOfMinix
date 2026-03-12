#pragma once

<<<<<<< HEAD
#include <stdint.h>
#include <lcom/lcf.h>
=======
#include <lcom/lcf.h>
#include <stdint.h>
>>>>>>> 20c8c3a53f16cfc0133721d61c000e721f50ecc6

typedef struct {
  uint8_t day;
  uint8_t month;
  uint8_t year;
} rtc_date;

/**
<<<<<<< HEAD
 * Reads the current date from the RTC and fills the provided rtc_date
=======
 * Reads the current date from the RTC and fills the provided `rtc_date`
>>>>>>> 20c8c3a53f16cfc0133721d61c000e721f50ecc6
 * structure. Returns 0 on success, non-zero on failure.
 *
 * This function takes care of ensuring data consistency by checking the Update
 * In Progress (UIP) flag before each read. It also should check the RTC
 * configuration and perform data conversions if necessary (e.g. BCD to binary).
 */
<<<<<<< HEAD
int rtc_read_date(rtc_date *date);
=======
int rtc_read_date(rtc_date *date);
>>>>>>> 20c8c3a53f16cfc0133721d61c000e721f50ecc6
