#pragma once

#define MAX_MINIONS 20

#include <lcom/lcf.h>
#include <stdlib.h>

#include "../champion/ChampionConfig.h"
#include "../champion/Champion.h"
#include "../minion/Minion.h"
#include "../tower/Tower.h"

#include "../../controller/MinionController.h"

#include "vbe.h"

typedef struct {
    Champion *p1;
    Champion *p2;
    Minions minions;
    Towers towers;
} GameState;

GameState *gameStateCreate();
void gameStateDestroy(GameState *gs);
