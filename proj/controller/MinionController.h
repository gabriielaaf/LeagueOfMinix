#pragma once

#include <stdlib.h>

#include "../model/minion/Minion.h"
#include "../model/minion/MinionConfig.h"
#include "../model/tower/Tower.h"
#include "../model/champion/Champion.h"
#include "../model/Box.h"


void minionsControllerInit(Minions *minions, int map_w);
void minionsUpdate(Minions *minions, Towers *towers, Champion *p1, Champion *p2, int map_w, bool second_elapsed);
int minionsTakeHit(Minions *minions, Box attack_box, int damage, Team attacker_team);
