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
} Game_state;

void game_init(Game_state *model);

void game_start(Game_state *game_state);
void game_pause(Game_state *game_state);
void game_resume(Game_state *game_state);
void game_over(Game_state *game_state, int winner);
void game_quit(Game_state *game_state);

#endif