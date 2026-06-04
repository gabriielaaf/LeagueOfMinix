#pragma once

#include "../model/minion/Minion.h"
#include "sprite/AnimSprite.h"
#include "HpBarViewer.h"
#include <lcom/lcf.h>

typedef struct {
    AnimSprite *idle;
    AnimSprite *atk;
    HpBarViewer *hpBar;
} MinionViewer;

MinionViewer *createMinionViewer(xpm_row_t *stop_xpm, xpm_row_t *atk_xpm);
void destroyMinionViewer(MinionViewer *viewer);
void minionViewerUpdate(MinionViewer *viewer);
int minionViewerDraw(MinionViewer *viewer, Minions *minions, Team team);
