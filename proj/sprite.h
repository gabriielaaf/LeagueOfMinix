#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <stdint.h>

#define TRANSPARENT_COLOR 255


typedef struct Sprite Sprite;

Sprite *sprite_create(xpm_map_t xpm, int x, int y);

void sprite_destroy(Sprite *sprite);

int sprite_draw(Sprite *sprite);

void sprite_set_position(Sprite *sprite, int x, int y);

void sprite_move(Sprite *sprite, int dx, int dy);

#endif
