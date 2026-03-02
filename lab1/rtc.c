#include "rtc.h"

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bcd_to_bin(uint8_t bcd) {
  uint8_t ms4 = bcd >> 4;
  uint8_t ls4 = bcd & 0x0F;
  return ms4 * 10 + ls4;
}

static int rtc_read_reg(uint8_t reg,uint8_t *value) {
  uint32_t tmp;
  if(sys_outb(RTC_ADDR_REG, reg)!= 0) return -1;
  
  if(sys_inb(RTC_DATA_REG, &tmp) != 0) return -1;
  *value = (uint8_t)tmp;
  return 0;
}

static int setup(void) {rtc_read_reg(RTC_REG_DAY);
  uint8_t a;

  do {
    a = rtc_read_reg(RTC_REG_A);
  } while (a & RTC_UIP_MSK);

  a = rtc_read_reg(RTC_REG_B);
  return (a & RTC_DM_MSK) != 0;
}

int rtc_read_date(rtc_date *date) {
  int is_binary = setup();

  uint8_t day;
  
  uint8_t month;
  uint8_t year;

  if(rtc_read_reg(RTC_REG_DAY, &day) != 0) return -1;
  if(rtc_read_reg(RTC_REG_MONTH, &month) != 0) return -1;
  if(rtc_read_reg(RTC_REG_YEAR, &year) != 0) return -1;

  if (!is_binary) {
    day = (uint8_t)bcd_to_bin(day);
    month = (uint8_t)bcd_to_bin(month);
    year = (uint8_t)bcd_to_bin(year);
  }

  date->day = day;
  date->month = month;
  date->year = year;

  return 0;
}