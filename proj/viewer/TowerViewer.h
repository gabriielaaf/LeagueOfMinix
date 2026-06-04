#pragma once

#include "../model/tower/Tower.h"
#include "HpBarViewer.h"

typedef struct {
    HpBarViewer *hpBar;
} TowerViewer;


TowerViewer *createTowerViewer();
void destroyTowerViewer(TowerViewer *viewer);
void towerViewerDraw(TowerViewer *viewer, Towers *towers);
