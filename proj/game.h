#ifndef GAME_H
#define GAME_H

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
} Game;

void game_init(Game *game);
void game_update(Game *game);
void game_draw(Game *game);

#endif