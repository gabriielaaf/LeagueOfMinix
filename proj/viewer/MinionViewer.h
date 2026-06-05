#pragma once

#include <stdlib.h>
#include <lcom/lcf.h>

#include "sprite/AnimSprite.h"
#include "HpBarViewer.h"

#include "../assets/minion_p1/minion_p1_xpms.h"
#include "../assets/minion_p2/minion_p2_xpms.h"

#include "../model/minion/MinionConfig.h"
#include "../model/minion/Minion.h"

typedef struct {
    AnimSprite *idle;
    AnimSprite *atk;
    HpBarViewer *hpBar;
} MinionViewer;

MinionViewer *createMinionViewer(xpm_row_t *stop_xpm, xpm_row_t *atk_xpm);
void destroyMinionViewer(MinionViewer *viewer);
void minionViewerUpdate(MinionViewer *viewer);
int minionViewerDraw(MinionViewer *viewer, Minions *minions, Team team);
