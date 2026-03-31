#pragma once

#include <stdint.h>
#include <stdbool.h>
typedef struct Scancode scancode;
extern bool kbd_error;

/* Keyboard interrupt management */
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int(void);
void (kbd_ih)(void);

/* Scancode interface */
void process_scancode_byte(uint8_t byte);

bool scancode_complete(void);
uint8_t get_scancode_size(void);
uint8_t* get_scancode_bytes(void);
void reset_scancode(void);
