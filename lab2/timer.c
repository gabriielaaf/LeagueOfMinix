#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
uint32_t counter = 0;

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {


  if (timer > 2 || freq == 0) return 1;
  

  uint8_t st;
  if (timer_get_conf(timer, &st) != 0) return 1;
  
  st &= 0x0F;

  st |=  (timer) << 6 | TIMER_LSB_MSB;

  if (sys_outb(TIMER_CTRL, st) != 0) return 1; 
  
  uint16_t divider = TIMER_FREQ / freq;
  uint8_t lsb, msb;

  util_get_LSB(divider, &lsb);
  util_get_MSB(divider, &msb);


  int port = TIMER_0 + timer;
 
  if (sys_outb(port, lsb) != 0) return 1;
  if (sys_outb(port, msb) != 0) return 1;


  return 0;
}



int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = BIT(hook_id);


  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) return 1;

}

int (timer_unsubscribe_int)() {

   if(sys_irqrmpolicy(&hook_id) != OK) return 1;

  return 0;

}

void (timer_int_handler)() {

  counter++;
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
