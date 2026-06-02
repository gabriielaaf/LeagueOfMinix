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

void gameStart(State *gameState);
void gamePause(State *gameState);
void gameResume(State *gameState);
void gameOver(State *gameState, int winner);
void gameQuit(State *gameState);

