#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "../model/champion/Champion.h"
#include "../model/champion/ChampionConfig.h"
#include "../model/minion/Minion.h"
#include "../model/Box.h"

void championUpdate(Champion *champion, bool animationLooped, bool second_elapsed);
void championMove(Champion *champion1, Champion *champion2, Minions *minions, int dx, int dy, int map_w, int map_h);

bool championAttack(Champion *champion);
bool championHits(Champion *attacker, Champion *target);

void championDecreaseHp(Champion *attacker, Champion *target, int dmg);
void championUpgradeHp(Champion *champion);
void championUpgradeDamage(Champion *champion);
void championUpgradeSpeed(Champion *champion);
