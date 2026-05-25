#ifndef CHAMPION_H
#define CHAMPION_H

#include <lcom/lcf.h>
#include "animSprite.h"
#include <stdint.h>
#include "vbe.h"

#define HP 100
#define SPEED 1
#define ATTACK_DMG 10
#define ATTACK_SPEED 5
#define COLLISION_PROPORTION 0.6
#define ATTACK_RANGE_OFFSET 0.05
#define RESPAWN_INTERRUPTS 180
#define ALIVE -1
#define BLUE_SPAWN_X 150
#define BLUE_SPAWN_Y (MODE105_HEIGHT / 2)
#define RED_SPAWN_X (MODE105_WIDTH - 150)
#define RED_SPAWN_Y (MODE105_HEIGHT / 2)

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

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Box;

typedef struct Champion Champion;

Champion *create_champion(int spawn_x, int spawn_y, AnimSprite **animations,int numAnimations, Direction dir);

void destroy_champion(Champion *champion);

void moveChampion(Champion *champion1, Champion *champion2, int dx, int dy);

void decrease_target_hp(struct Champion *attacker,
                             struct Champion *target);

void champion_set_animation(Champion *champion, int animation);

bool champion_attack(Champion *champion);

void champion_update(Champion *champion);

int champion_draw(Champion *champion);

Box champion_get_collision_box(Champion *champion);

Box champion_get_attack_box(Champion *champion);

bool champion_is_attacking(Champion *champion);

bool champion_attack_hits(Champion *attacker, Champion *target);

#endif
