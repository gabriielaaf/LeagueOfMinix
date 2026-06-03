#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <stdint.h>

#define TRANSPARENT_COLOR 255

typedef struct Sprite Sprite;

Sprite *spriteCreate(xpm_map_t xpm);

void spriteDestroy(Sprite *sprite);

int spriteDraw(Sprite *sprite, int x, int y);

int getWidth(Sprite *sprite);

int getHeight(Sprite *sprite);

#endif
