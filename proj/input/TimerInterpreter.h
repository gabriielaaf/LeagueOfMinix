#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int ticks_per_update;
    int tick_counter;
    uint32_t total_ticks;
    bool should_update;
} TimerState;

void timerStateInit(TimerState *state, int ticks_per_update);

void timerInterpretInterrupt(TimerState *state);
