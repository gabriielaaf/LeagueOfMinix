#pragma once

#include <stdbool.h>

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
} StateType;

typedef struct {
    StateType state;
    bool running;
    int winner;
} State;

void stateInit(State *model);

void gameStart(State *game_state);
void gamePause(State *game_state);
void gameResume(State *game_state);
void gameOver(State *game_state, int winner);
void gameQuit(State *game_state);

