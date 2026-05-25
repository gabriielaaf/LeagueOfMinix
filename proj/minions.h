#ifndef MINIONS_H
#define MINIONS_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "vbe.h"
#include "champion.h"

#define MINION_W        30
#define MINION_H        40
#define MINION_COUNT    2
#define MINION_LANE_Y   330
#define MINION_SPACING  15
#define MAX_WAVES       8
#define SPAWN_INTERVAL  300  /* 15s at 20 UPS */

typedef enum {
    MINION_RED,
    MINION_BLUE
} MinionTeam;

typedef enum {
    MINION_MOVING,
    MINION_ATTACKING,
    MINION_DEAD
} MinionState;

typedef struct {
    int x, y;
    int hp;
    MinionTeam team;
    MinionState state;
    int attack_timer;
} Minion;

typedef struct {
    Minion minions[MINION_COUNT];
    bool active;
} MinionWave;

typedef struct {
    MinionWave red_waves[MAX_WAVES];
    MinionWave blue_waves[MAX_WAVES];
    int red_count;
    int blue_count;
    int spawn_timer;
} MinionsManager;

void minions_manager_init(MinionsManager *mgr);
void update_minions_manager(MinionsManager *mgr);
int draw_minions_manager(MinionsManager *mgr);
void minions_manager_take_hit(MinionsManager *mgr, Box attack_box, int damage);

#endif
