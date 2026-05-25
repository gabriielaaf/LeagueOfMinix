#ifndef CHAMPION_H
#define CHAMPION_H

#include <lcom/lcf.h>
#include "animSprite.h"
#include <stdint.h>
#include "vbe.h"

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
    int x;
    int y;
    int w;
    int h;
} Box;

typedef struct Champion Champion;

Champion *create_champion(int x, int y, AnimSprite **animations,int numAnimations);

void destroy_champion(Champion *champion);

void moveChampion(Champion *champion1, Champion *champion2, int dx, int dy);

void decrease_target_hp(struct Champion *attacker,
                             struct Champion *target);

void champion_set_animation(Champion *champion, int animation);

void champion_attack(Champion *champion);

void champion_update(Champion *champion);

int champion_draw(Champion *champion);

Box champion_get_collision_box(Champion *champion);

Box champion_get_attack_box(Champion *champion);

bool champion_attack_hits(Champion *attacker, Champion *target);

#endif
