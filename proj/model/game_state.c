#include <lcf.h>

#include "game_state.h"

void game_init(Game_state *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_MENU;
    game_state->running = true;
    game_state->winner = 0;
}

void game_start(Game_state *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PLAYING;
    game_state->winner = 0;
}

void game_pause(Game_state *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PAUSED;
}

void game_resume(Game_state *game_state) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_PLAYING;
}

void game_over(Game_state *game_state, int winner) {
    if (game_state == NULL) return;

    game_state->state = GAME_STATE_GAME_OVER;
    game_state->winner = winner;
}

void game_quit(Game_state *game_state) {
    if (game_state == NULL) return;

    game_state->running = false;
}