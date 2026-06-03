#pragma once

#include <stdbool.h>

#include "GameState.h"
#include "../../input/KeyboardInterpreter.h"
#include "../../input/MouseInterpreter.h"
#include "MenuState.h"


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

    GameState *game;
    MenuState *menu;

} State;

bool stateInit(State *state);
void stateDestroy(State *state);

void gameStart(State *state);
void gamePause(State *state);
void gameResume(State *state);
void gameOver(State *state, int winner);
void gameQuit(State *state);

void stateStep(State *state, KeyboardState *kbd, MouseState *mouse);
