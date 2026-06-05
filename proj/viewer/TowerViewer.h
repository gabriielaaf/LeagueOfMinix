#pragma once

#include "../model/tower/Tower.h"
#include "HpBarViewer.h"
#include "sprite/Sprite.h"

typedef struct {
    HpBarViewer *hpBar;
    Sprite *blue;
    Sprite *red;
} TowerViewer;


TowerViewer *createTowerViewer(xpm_map_t xpm_blue, xpm_map_t xpm_red);
void destroyTowerViewer(TowerViewer *viewer);
void towerViewerDraw(TowerViewer *viewer, Towers *towers);
