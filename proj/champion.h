#ifndef CHAMPION_H
#define CHAMPION_H

#include <lcom/lcf.h>
#include "animSprite.h"
#include <stdint.h>

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
    CHAMPION_IDLE,
    CHAMPION_MOVING,
    CHAMPION_ATTACKING
} ChampionState;

typedef struct Champion Champion;

Champion *create_champion(int x, int y, AnimSprite **animations,int numAnimations);

void destroy_champion(Champion *champion);

void moveChampion(Champion *champion, int dx, int dy);

void attack_damaged_champion(struct Champion *champion_attacking,
                             struct Champion *champion_attacked);

void ability_damaged_champion(struct Champion *champion_attacking,
                              struct Champion *champion_attacked);

void champion_set_animation(Champion *champion, int animation);

void champion_attack(Champion *champion);

void champion_update(Champion *champion);

int champion_draw(Champion *champion);

#endif
