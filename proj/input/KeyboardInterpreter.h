#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
} PlayerInput;

typedef struct {
    PlayerInput p1;
    PlayerInput p2;
    
    bool exit;
} KeyboardState;

void keyboardStateInit(KeyboardState *state);

void keyboardInterpretScancode(KeyboardState *state, uint8_t *bytes, uint8_t size);
