#include <lcom/lcf.h>

#include "game_state.h"

void game_state_init(GameState *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_MENU;
    game_state->running = true;
    game_state->winner = 0;
}

void game_state_start(GameState *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PLAYING;
    game_state->winner = 0;
}

void game_state_pause(GameState *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PAUSED;
}

void game_state_resume(GameState *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PLAYING;
}

void game_state_over(GameState *game_state, int winner) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_GAME_OVER;
    game_state->winner = winner;
}

void game_state_quit(GameState *game_state) {
    if (game_state == NULL) return;

    game_state->running = false;
}