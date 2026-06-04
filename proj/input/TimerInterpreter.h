#pragma once

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int ticks_per_update;
    int tick_counter;
    uint32_t total_ticks;
    bool should_update;
    bool second_elapsed;
} TimerState;

void timerStateInit(TimerState *state, int ticks_per_update);

void timerInterpretInterrupt(TimerState *state);
