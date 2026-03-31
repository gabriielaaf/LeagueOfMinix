#include "keyboard.h"
#include "i8042.h"

int hook_id = KBD_IRQ;
bool kbd_error = false;

struct Scancode {
    uint8_t bytes[2];
    uint8_t size;
    bool complete;
};

static struct Scancode current_scancode = {{0, 0}, 0, false};

int (kbd_subscribe_int)(uint8_t *bit_no) {
    *bit_no = hook_id;
    if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) return 1;
    return 0;
}

int (kbd_unsubscribe_int)(void) {
    if (sys_irqrmpolicy(&hook_id) != 0) return 1;
    return 0;
}

void (kbd_ih)(void) {
    uint8_t status;
    uint8_t byte;
    if (util_sys_inb(STATUS_REGISTER, &status) != 0) { kbd_error = true; return; }
    if (status & (TIMEOUT_ERROR | PARITY_ERROR)) { kbd_error = true; return; }
    if (util_sys_inb(OUTPUT_BUFFER, &byte) != 0) { kbd_error = true; return; }
    process_scancode_byte(byte);
}

void process_scancode_byte(uint8_t byte) {
    if (byte == CODE_PREFIX) {
        current_scancode.bytes[0] = byte;
        current_scancode.size = 2;
        current_scancode.complete = false;
    } else {
        if (current_scancode.size == 2 && !current_scancode.complete) {
            current_scancode.bytes[1] = byte;
            current_scancode.complete = true;
        } else {
            current_scancode.bytes[0] = byte;
            current_scancode.size = 1;
            current_scancode.complete = true;
        }
    }
}

bool scancode_complete(void) { 
  return current_scancode.complete; 
}
uint8_t get_scancode_size(void) {
   return current_scancode.size; 
}
uint8_t *get_scancode_bytes(void) {
   return current_scancode.bytes; 
  }
void reset_scancode(void) { 
  current_scancode.complete = false; current_scancode.size = 0; 
}
