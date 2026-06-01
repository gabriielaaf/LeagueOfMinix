#ifndef TIMER_INTERPRETER_H
#define TIMER_INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int ticks_per_update;
    int tick_counter;
    uint32_t total_ticks;
    bool should_update;
} TimerState;

void timer_state_init(TimerState *state, int ticks_per_update);

void timer_interpret_interrupt(TimerState *state);

#endif
