#include "rtc.h"

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bdc_to_bin(uint8_t bcd) {


 }

static int setup(){

  uint8_t a;
  uint32_t tmp;

  do {
    sys_outb(RTC_ADDR_REG, RTC_REG_A);
    sys_inb(RTC_DATA_REG, &tmp);
    a = (uint8_t) tmp;
  } while (a & RTC_UIP_MSK);

  sys_outb(RTC_ADDR_REG, RTC_REG_B);
  sys_inb(RTC_DATA_REG, &tmp);
  a = (uint8_t) tmp;

  return  (a & RTC_DM_MSK) != 0;

}


int rtc_read_date(rtc_date *date) { 
  
  


}
