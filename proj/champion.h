#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <stdint.h>

#include "sprite.h"

typedef struct Champion Champion;

Champion *create_champion(int x, int y, int hp, int speed, int ad, int ap);

#endif
