#pragma once

#include <stdbool.h>
#include "../model/champion/Champion.h"
#include "../model/minion/Minion.h"
#include "ChampionViewer.h"
#include "MinionViewer.h"

typedef struct {
    ChampionViewer *p1;
    ChampionViewer *p2;
    MinionViewer *minion_blue;
    MinionViewer *minion_red;
} GameViewer;

GameViewer *gameViewerCreate();
void gameViewerDestroy(GameViewer *gv);
void gameViewerUpdate(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions, bool *p1_looped, bool *p2_looped);
void gameViewerDraw(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions);
