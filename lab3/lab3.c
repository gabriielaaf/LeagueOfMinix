#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "keyboard.h"
#include "i8042.h"
#include <stdbool.h>
#include <stdint.h>
#define DELAY_US 20000

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (kbd_test_scan)(void) {
    int r, ipc_status;
    message msg;
    bool running = true;
    uint8_t bit_no;

    if (kbd_subscribe_int(&bit_no) != 0) return 1;
    uint32_t irq_set = BIT(bit_no);

    while (running) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_set) {
                        kbd_ih();
                        if (kbd_error) {
                            kbd_error = false;
                            reset_scancode();
                            continue;
                        }
                        if (scancode_complete()) {
                            uint8_t size = get_scancode_size();
                            uint8_t *bytes = get_scancode_bytes();
                            bool is_make = !(bytes[size - 1] & BREAKCODE);
                            if (size == 1 && bytes[0] == (ESC | BREAKCODE)) running = false;
                            if (kbd_print_scancode(is_make, size, bytes) != 0) return 1;
                            reset_scancode();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (kbd_unsubscribe_int() != 0) return 1;
    return 0;
}

int(kbd_test_poll)() {
    uint8_t scancode;
    uint8_t status;
    bool running = true;

    if (disable_keyboard_interrupts() != 0)
        return 1;

    while (running) {

        if (sys_inb(STATUS_REGISTER, &status) != 0)
            continue;

        if (status & OUTPUT_BUFFER_FULL) {

            if (sys_inb(OUTPUT_BUFFER, &scancode) != 0)
                continue;

            if (status & (PARITY_ERROR | TIMEOUT_ERROR))
                continue;

            process_scancode_byte(scancode);

            if (scancode_complete()) {

                uint8_t *bytes = get_scancode_bytes();
                uint8_t size = get_scancode_size();
                bool is_make = !(bytes[size-1] & BREAKCODE);

                if (kbd_print_scancode(is_make, size, bytes) != 0) continue;

                if (bytes[0] == (ESC | BREAKCODE)) {
                    running = false;
                }

                reset_scancode();
            }
        }

        tickdelay(micros_to_ticks(DELAY_US));
    }
    return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
