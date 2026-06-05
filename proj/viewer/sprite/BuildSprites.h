#pragma once

/** @brief Total number of champion animation clips (8 directions × 3 states). */
#define NUM_ANIMS 12
/** @brief Number of frames in each attack animation. */
#define ATTACK_FRAMES 2
/** @brief Ticks per frame for attack animations. */
#define ATTACK_TIME 20
/** @brief Number of frames in each walk animation. */
#define MOVE_FRAMES 2
/** @brief Ticks per frame for walk animations. */
#define MOVE_TIME 10

#include <stdlib.h>

#include "Sprite.h"
#include "AnimSprite.h"

#include "../../assets/p1/p1_north_xpms.h"
#include "../../assets/p1/p1_south_xpms.h"
#include "../../assets/p1/p1_east_xpms.h"
#include "../../assets/p1/p1_west_xpms.h"

/**
 * @brief Builds the full set of champion AnimSprite clips for the given player.
 *
 * Returns a heap-allocated array of NUM_ANIMS pointers laid out as:
 *  - [0..7]   Idle animations for each of the 8 directions.
 *  - [8..15]  Attack animations for each of the 8 directions.
 *  - [16..23] Walk animations for each of the 8 directions.
 *
 * The direction order within each group matches the Direction enum
 * (NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST).
 *
 * @param player Player index (1 for blue, 2 for red).
 * @return Heap-allocated array of NUM_ANIMS AnimSprite pointers, or NULL on failure.
 */
AnimSprite **buildAnimations(int player);
