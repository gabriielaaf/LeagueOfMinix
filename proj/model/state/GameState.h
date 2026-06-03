#pragma once

#include "../champion/Champion.h"
#include "../minion/Minion.h"
#include "../../input/KeyboardInterpreter.h"
#include "../../input/MouseInterpreter.h"
#include "../../viewer/GameViewer.h"
#include "../../controller/GameController.h"

typedef struct {
    Champion *p1;
    Champion *p2;
    Minions minions;
    GameController *ctrl;
    GameViewer *viewer;
} GameState;

GameState *gameStateCreate();
void gameStateDestroy(GameState *gs);
void gameStateStep(GameState *gs, KeyboardState *kbd, MouseState *mouse);
void gameStateDraw(GameState *gs);
