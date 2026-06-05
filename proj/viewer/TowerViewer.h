#pragma once

#include "sprite/Sprite.h"
#include "HpBarViewer.h"

#include "../model/tower/Tower.h"
#include "../model/tower/TowerConfig.h"

#include "video.h"


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
