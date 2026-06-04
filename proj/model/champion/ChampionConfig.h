#pragma once

#include "../Position.h"
#include "vbe.h"

#define CHAMPION_W 64
#define CHAMPION_H 68

#define CHAMPION_HP 100
#define CHAMPION_SPEED 1.3
#define CHAMPION_ATTACK_DMG 10
#define COLLISION_PROPORTION 0.8
#define ATTACK_RANGE_OFFSET 0.05
#define RESPAWN_SECONDS 9
#define ALIVE -1

#define BLUE_SPAWN (Position){0, 0}
#define RED_SPAWN (Position){MODE105_WIDTH - CHAMPION_W, 0}
