#pragma once

#include <math.h>

#include "../model/tower/TowerConfig.h"
#include "../model/tower/Tower.h"
#include "../model/minion/MinionConfig.h"
#include "../model/minion/Minion.h"
#include "../model/champion/Champion.h"

#include "../model/Box.h"

#include "ChampionController.h"



void towerTakeHit(Tower *t, Box attack_box, int dmg);
void towersUpdate(Towers *towers, Minions *minions, Champion *p1, Champion *p2);
void towersTakeHit(Towers *towers, Box attack_box, int damage, Team attacker_team);
