#pragma once

#include "../model/Champion.h"
#include "../animSprite.h"

typedef struct {
    AnimSprite **animations;
    int numAnimations;
    int currentAnimation;
} ChampionViewer;

int champion_draw(Champion *champion);
