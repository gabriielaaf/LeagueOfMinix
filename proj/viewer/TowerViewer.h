#pragma once

#include "../model/tower/Tower.h"
#include "HpBarViewer.h"
#include "sprite/Sprite.h"
#include "sprite/AnimSprite.h"

typedef struct {
    HpBarViewer *hpBar;
    Sprite *blue;
    Sprite *red;
    AnimSprite *blueProjectile;
    AnimSprite *redProjectile;
} TowerViewer;


TowerViewer *createTowerViewer(xpm_map_t xpm_blue, xpm_map_t xpm_red);
void destroyTowerViewer(TowerViewer *viewer);
void towerViewerDraw(TowerViewer *viewer, Towers *towers);
