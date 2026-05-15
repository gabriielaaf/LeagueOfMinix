#ifndef KEYBOARD_INTERPRETER_H
#define KEYBOARD_INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool attack;
} PlayerInput;

typedef struct {
    PlayerInput p1;
    PlayerInput p2;
    bool exit;
} KeyboardState;

void keyboard_state_init(KeyboardState *state);

void keyboard_interpret_scancode(KeyboardState *state, uint8_t *bytes, uint8_t size);

#endif
