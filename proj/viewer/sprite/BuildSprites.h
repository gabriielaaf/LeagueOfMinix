#pragma once

#define NUM_ANIMS 24
#define ATTACK_FRAMES 3
#define ATTACK_TIME 20
#define MOVE_FRAMES 2
#define MOVE_TIME 10

#include "AnimSprite.h"

#include "../../assets/p1/p1_north_xpms.h"
#include "../../assets/p1/p1_south_xpms.h"
#include "../../assets/p1/p1_east_xpms.h"
#include "../../assets/p1/p1_west_xpms.h"
#include "../../assets/p1/p1_north_east_xpms.h"
#include "../../assets/p1/p1_north_west_xpms.h"
#include "../../assets/p1/p1_south_east_xpms.h"
#include "../../assets/p1/p1_south_west_xpms.h"

#include "../../assets/p2/p2_north_xpms.h"
#include "../../assets/p2/p2_south_xpms.h"
#include "../../assets/p2/p2_east_xpms.h"
#include "../../assets/p2/p2_west_xpms.h"
#include "../../assets/p2/p2_north_east_xpms.h"
#include "../../assets/p2/p2_north_west_xpms.h"
#include "../../assets/p2/p2_south_east_xpms.h"
#include "../../assets/p2/p2_south_west_xpms.h"

#include "Sprite.h"

AnimSprite **buildAnimations(int player);
