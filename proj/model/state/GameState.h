#pragma once

#define MAX_MINIONS 20

#include "../champion/Champion.h"
#include "../minion/Minion.h"
#include "../tower/Tower.h"

typedef struct {
    Champion *p1;
    Champion *p2;
    Minions minions;
    Towers towers;
} GameState;

GameState *gameStateCreate();
void gameStateDestroy(GameState *gs);
