#pragma once

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdlib.h>

#include "video.h"

#define TRANSPARENT_COLOR 255

typedef struct Sprite Sprite;

Sprite *spriteCreate(xpm_map_t xpm);

const uint8_t *spriteGetMap(const Sprite *sprite);

void spriteDestroy(Sprite *sprite);

int spriteDraw(Sprite *sprite, int x, int y);

int getWidth(Sprite *sprite);

int getHeight(Sprite *sprite);
