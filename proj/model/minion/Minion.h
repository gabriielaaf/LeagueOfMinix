#pragma once

#include <stdbool.h>
#include "../Position.h"
#include "../champion/Champion.h"
#include "MinionConfig.h"

typedef enum {
    MINION_MOVING,
    MINION_ATTACKING,
    MINION_DEAD
} MinionState;

typedef struct {
    Position pos;
    Team team;
    MinionState state;
    int hp;
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
} Minions;

void minionsInit(Minions *minions);
