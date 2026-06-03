#pragma once

#include <lcom/lcf.h>

#include "State.h"

void stateInit(State *state) {
    if (state == NULL) return;

    state->state = STATE_MENU;
    state->running = true;
    state->winner = 0;
}

void gameStart(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
    state->winner = 0;
}

void gamePause(State *state) {
    if (state == NULL) return;

    state->state = STATE_PAUSED;
}

void gameResume(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
}

void gameOver(State *state, int winner) {
    if (state == NULL) return;

    state->state = STATE_GAME_OVER;
    state->winner = winner;
}

void gameQuit(State *state) {
    if (state == NULL) return;

    state->running = false;
}