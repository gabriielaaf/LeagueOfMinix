#pragma once

#include "../model/tower/Tower.h"
#include "../model/minion/Minion.h"
#include "../model/champion/Champion.h"
#include "../model/Box.h"

void towersUpdate(Towers *towers, Minions *minions, Champion *p1, Champion *p2);
void towersTakeHit(Towers *towers, Box attack_box, int damage, Team attacker_team);
