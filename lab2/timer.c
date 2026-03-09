#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {


  uint8_t mask = TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ | TIMER_RB_CMD;
  sys_outb(TIMER_CTRL,mask);
  util_sys_inb(TIMER_0 + timer,st);


  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
 

    union timer_status_field_val conf_val;

    switch(field) {

    case tsf_all:
        conf_val.byte = st;
        break;

    case tsf_initial:
        conf_val.in_mode = (st >> 4) & 0x03;
        break;

    case tsf_mode: {
        uint8_t mode = (st >> 1) & 0x07;

        if (mode > 5)
            mode -= 4;

        conf_val.count_mode = mode;
        break;
    }

    case tsf_base:
        conf_val.bcd = st & TIMER_BCD;
        break;

    default:
        return 1;
}

    return timer_print_config(timer, field, conf_val);                        

}
