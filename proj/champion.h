#ifndef CHAMPION_H
#define CHAMPION_H

#include <lcom/lcf.h>
#include "animSprite.h"
#include <stdint.h>


typedef struct Champion Champion;

Champion *create_champion(int x, int y, AnimSprite **animations,int numAnimations);

void destroy_champion(Champion *champion);

void moveChampion(Champion *champion, int dx, int dy);

void champion_set_animation(Champion *champion, int animation);

void champion_update(Champion *champion);

int champion_draw(Champion *champion);

#endif
