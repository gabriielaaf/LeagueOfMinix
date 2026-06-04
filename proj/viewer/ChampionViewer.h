#pragma once

#include "../model/champion/Champion.h"
#include "sprite/AnimSprite.h"
#include "HpBarViewer.h"
#include <stdbool.h>

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
