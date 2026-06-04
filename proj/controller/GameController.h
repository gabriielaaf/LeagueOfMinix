#pragma once

#include "ChampionController.h"
#include "MinionController.h"
#include "TowerController.h"
#include "../input/KeyboardInterpreter.h"
#include "../input/MouseInterpreter.h"
#include "vbe.h"

typedef struct {
    int map_w;
    int map_h;
} GameController;

GameController *gameControllerCreate(int map_w, int map_h);
void gameControllerDestroy(GameController *gc);
void gameControllerUpdate(GameController *gc, Champion *p1, Champion *p2, Minions *minions,
                          Towers *towers, KeyboardState *kbd, MouseState *mouse);
