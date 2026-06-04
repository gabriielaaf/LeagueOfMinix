#pragma once

#define MAX_MINIONS 20

#include "../champion/Champion.h"
#include "../minion/Minion.h"

typedef struct {
    Champion *p1;
    Champion *p2;
    Minions minions;
} GameState;

GameState *gameStateCreate();
void gameStateDestroy(GameState *gs);
