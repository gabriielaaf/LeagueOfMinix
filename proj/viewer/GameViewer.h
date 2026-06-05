#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "sprite/BuildSprites.h"
#include "ChampionViewer.h"
#include "MinionViewer.h"
#include "TowerViewer.h"

#include "../assets/minion_p1/minion_p1_xpms.h"
#include "../assets/minion_p2/minion_p2_xpms.h"
#include "../assets/tower_p1_xpm.h"
#include "../assets/tower_p2_xpm.h"

#include "../model/champion/Champion.h"
#include "../model/minion/Minion.h"
#include "../model/tower/Tower.h"

typedef struct {
    ChampionViewer *p1;
    ChampionViewer *p2;
    MinionViewer *minion_blue;
    MinionViewer *minion_red;
    TowerViewer *tower;
} GameViewer;

GameViewer *gameViewerCreate();
void gameViewerDestroy(GameViewer *gv);
void gameViewerUpdate(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions, bool *p1_looped, bool *p2_looped);
void gameViewerDraw(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions, Towers *towers);
