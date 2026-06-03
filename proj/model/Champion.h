#pragma once

#include "Position.h"
#include "../animSprite.h"

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST
} Direction;

typedef enum {
    TEAM_RED,
    TEAM_BLUE
} Team;

typedef enum {
    CHAMPION_IDLE,
    CHAMPION_MOVING,
    CHAMPION_ATTACKING
} ChampionState;

typedef struct {
    ChampionState state;
    Position respawnPos;
    Position pos;
    Direction dir;
    Team team;

    int hp;
    int speed;
    int attack_dmg;
    int respawn_timer;
} Champion;


