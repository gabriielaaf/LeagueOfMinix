#pragma once

#include "../model/Champion.h"

void championUpdate(Champion *champion);

void championMove(Champion *champion1, Champion *champion2, int dx, int dy);

bool championAttack(Champion *champion);

bool championHits(Champion *attacker, Champion *target);

void championDecreaseHp(Champion *attacker, int hp);

void championUpgradeHp(Champion *champion);

void championUpgradeDamage(Champion *champion);

void championUpgradeSpeed(Champion *champion);
