#pragma once

#include <stdlib.h>
#include "../model/minion/Minion.h"
#include "../model/minion/MinionConfig.h"
#include "../model/Box.h"

void minionsControllerInit(Minions *minions, int map_w);
void minionsUpdate(Minions *minions, int map_w);
void minionsTakeHit(Minions *minions, Box attack_box, int damage, Team attacker_team);
