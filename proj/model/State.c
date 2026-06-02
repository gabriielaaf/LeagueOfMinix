#include <lcom/lcf.h>

#include "State.h"

void stateInit(State *state) {
    if (state == NULL) return;

    state->state = STATE_MENU;
    state->running = true;
    state->winner = 0;
}

void statestart(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
    state->winner = 0;
}

void statepause(State *state) {
    if (state == NULL) return;

    state->state = STATE_PAUSED;
}

void stateresume(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
}

void stateover(State *state, int winner) {
    if (state == NULL) return;

    state->state = STATE_OVER;
    state->winner = winner;
}

void statequit(State *state) {
    if (state == NULL) return;

    state->running = false;
}