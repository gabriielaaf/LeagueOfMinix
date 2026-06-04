#pragma once

#include "../model/tower/Tower.h"
#include "../model/minion/Minion.h"
#include "../model/champion/Champion.h"
#include "../model/Box.h"

void towerTakeHit(Tower *t, Box attack_box, int dmg);
void towersUpdate(Towers *towers, Minions *minions, Champion *p1, Champion *p2);
