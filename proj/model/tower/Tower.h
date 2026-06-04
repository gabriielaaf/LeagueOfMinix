#pragma once

#include "../Position.h"
#include "../champion/Champion.h"
#include "../minion/Minion.h"
#include "TowerConfig.h"
#include <stdbool.h>

typedef struct {
    Position pos;
    Minion *minion_target;
    bool targeting_champion;
    bool active;
    int damage;
} TowerProjectile;

typedef struct {
  Position pos;
  Team team;
  int hp;
  int attack_timer;
  Minion *minion_target;
  bool targeting_champion;
  TowerProjectile projectile;
} Tower;

typedef struct {
  Tower blue;
  Tower red;
} Towers;

void towersInit(Towers *towers, int map_w);
