#pragma once

#include <lcom/lcf.h>
#include "../Position.h"

#define CHAMPION_HP 100
#define CHAMPION_SPEED 1
#define CHAMPION_ATTACK_DMG 10
#define COLLISION_PROPORTION 0.8
#define ATTACK_RANGE_OFFSET 0.05
#define RESPAWN_SECONDS 9
#define ALIVE -1

#define BLUE_SPAWN (Position){150, MODE105_HEIGHT / 2}
#define RED_SPAWN (Position){MODE105_WIDTH - 150, MODE105_HEIGHT / 2}