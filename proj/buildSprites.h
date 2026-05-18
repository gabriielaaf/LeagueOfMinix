#ifndef BUILDSPRITES_H
#define BUILDSPRITES_H

#define NUM_ANIMS 16
#define ATTACK_FRAMES 3
#define ATTACK_TIME 5

#include "animSprite.h"

#include "assets/p1/p1_north_xpms.h"
#include "assets/p1/p1_south_xpms.h"
#include "assets/p1/p1_east_xpms.h"
#include "assets/p1/p1_west_xpms.h"
#include "assets/p1/p1_north_east_xpms.h"
#include "assets/p1/p1_north_west_xpms.h"
#include "assets/p1/p1_south_east_xpms.h"
#include "assets/p1/p1_south_west_xpms.h"

#include "assets/p2/p2_north_xpms.h"
#include "assets/p2/p2_south_xpms.h"
#include "assets/p2/p2_east_xpms.h"
#include "assets/p2/p2_west_xpms.h"
#include "assets/p2/p2_north_east_xpms.h"
#include "assets/p2/p2_north_west_xpms.h"
#include "assets/p2/p2_south_east_xpms.h"
#include "assets/p2/p2_south_west_xpms.h"

#include "sprite.h"

AnimSprite **build_animations();

#endif
