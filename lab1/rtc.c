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
static uint8_t rtc_read_reg(uint8_t reg) {
  uint32_t tmp;
  sys_outb(RTC_ADDR_REG, reg);
  sys_inb(RTC_DATA_REG, &tmp);
  return (uint8_t) tmp;
}


static int setup(){

  uint8_t a;
  uint32_t tmp;

  do {
    a = rtc_read_reg(RTC_REG_A);
  } while (a & RTC_UIP_MSK);

  a = rtc_read_reg(RTC_REG_B);
  a = (uint8_t) tmp;

  return  (a & RTC_DM_MSK) != 0;

}




int rtc_read_date(rtc_date *date) { 

    TODO;

    
}
