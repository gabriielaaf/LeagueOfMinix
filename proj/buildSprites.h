#ifndef BUILDSPRITES_H
#define BUILDSPRITES_H

#define NUM_ANIMS 16
#define ATTACK_FRAMES 3
#define ATTACK_TIME 5

#include "animSprite.h"
#include "assets/yasuo_east_xpms.h"
#include "assets/yasuo_north_xpms.h"
#include "assets/yasuo_north_east_xpms.h"
#include "assets/yasuo_north_west_xpms.h"
#include "assets/yasuo_south_east_xpms.h"
#include "assets/yasuo_south_west_xpms.h"
#include "assets/yasuo_south_xpms.h"
#include "assets/yasuo_west_xpms.h"
#include "sprite.h"

AnimSprite **build_animations();

#endif
