#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "sprite/AnimSprite.h"
#include "HpBarViewer.h"

#include "../model/champion/Champion.h"

typedef struct {
    AnimSprite **animations;
    int numAnimations;
    int currentAnimation;
    HpBarViewer *hpBar;
} ChampionViewer;

ChampionViewer *createChampionViewer(AnimSprite **animations, int numAnimations);
void destroyChampionViewer(ChampionViewer *viewer);
bool championViewerUpdate(ChampionViewer *viewer, Champion *champion);
int championDraw(ChampionViewer *viewer, Champion *champion);
