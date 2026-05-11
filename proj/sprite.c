#include "sprite.h"
#include "video.h"

#include <stdlib.h>


struct Sprite {
  int x;
  int y;

  int width;
  int height;

  uint8_t *map;
};

Sprite *sprite_create(xpm_map_t xpm, int x, int y) {
  Sprite *sprite = malloc(sizeof(Sprite));

  if (sprite == NULL) {
    return NULL;
  }

  xpm_image_t img;

  sprite->map = xpm_load(xpm, XPM_INDEXED, &img);

  if (sprite->map == NULL) {
    free(sprite);
    return NULL;
  }

  sprite->x = x;
  sprite->y = y;
  sprite->width = img.width;
  sprite->height = img.height;

  return sprite;
}

void sprite_destroy(Sprite *sprite) {
  if (sprite == NULL) {
    return;
  }

  if (sprite->map != NULL) {
    free(sprite->map);
  }

  free(sprite);
}

int sprite_draw(Sprite *sprite) {
  if (sprite == NULL || sprite->map == NULL) {
    return 1;
  }

  return vg_draw_pixmap(sprite->map,sprite->width,sprite->height,sprite->x,sprite->y,TRANSPARENT_COLOR);
}

void sprite_set_position(Sprite *sprite, int x, int y) {
  if (sprite == NULL) {
    return;
  }

  sprite->x = x;
  sprite->y = y;
}

void sprite_move(Sprite *sprite, int dx, int dy) {
  if (sprite == NULL) {
    return;
  }

  sprite->x += dx;
  sprite->y += dy;
}

