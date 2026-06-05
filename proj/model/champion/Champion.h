#pragma once

#include <stdlib.h>

#include "ChampionConfig.h"

#include "../Position.h"
#include "../Box.h"

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

typedef struct Champion Champion;

Champion *createChampion(Position respawnPos, Direction dir, int width, int height);
void destroyChampion(Champion *champion);
void championRespawn(Champion *champion);

Position championGetPos(Champion *champion);
Direction championGetDir(Champion *champion);
ChampionState championGetState(Champion *champion);

float championGetSpeed(Champion *champion);
int championGetHp(Champion *champion);
int championGetMaxHp(Champion *champion);
int championGetAttackDmg(Champion *champion);
int championGetRespawnTimer(Champion *champion);
int championGetWidth(Champion *champion);
int championGetHeight(Champion *champion);

void championSetState(Champion *champion, ChampionState state);
void championSetDir(Champion *champion, Direction dir);
void championSetPos(Champion *champion, Position pos);
void championSetHp(Champion *champion, int hp);
void championSetRespawnTimer(Champion *champion, int timer);

void championClearPosition(Champion *champion);
void championAddHp(Champion *champion, int delta);
void championAddMaxHp(Champion *champion, int delta);
void championAddSpeed(Champion *champion, int delta);
void championAddAttackDmg(Champion *champion, int delta);
Box championGetCollisionBox(Champion *champion);
Box championGetAttackBox(Champion *champion);

bool championAttackHits(Champion *attacker, Champion *target);

int championCurrentPoints(Champion *champion);
void championUpdatePoints(Champion *champion, int delta);
