#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_GAME_OVER
} GameStateType;

typedef struct {
    GameStateType state;
    bool running;
    int winner;
} GameState;

void game_init(GameState *model);

void game_start(GameState *game_state);
void game_pause(GameState *game_state);
void game_resume(GameState *game_state);
void game_over(GameState *game_state, int winner);
void game_quit(GameState *game_state);

#endif