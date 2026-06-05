#include "Sprite.h"
#include "video.h"

#include <stdlib.h>


struct Sprite {
    int width;
    int height;

    uint8_t *map;
};

Sprite *spriteCreate(xpm_map_t xpm) {
    Sprite *sprite = malloc(sizeof(Sprite));
    if (sprite == NULL) {
        return NULL;
    }

    xpm_image_t img;

    sprite->map = xpm_load(xpm, XPM_8_8_8, &img);

    if (sprite->map == NULL) {
        free(sprite);
        return NULL;
    }

    sprite->width = img.width;
    sprite->height = img.height;

    return sprite;
}

const uint8_t *spriteGetMap(const Sprite *sprite) {
    if (sprite == NULL) {
        return NULL;
    }

    return sprite->map;
}

void spriteDestroy(Sprite *sprite) {
    if (sprite == NULL) {
        return;
    }

    if (sprite->map != NULL) {
        free(sprite->map);
    }

    free(sprite);
}

int spriteDraw(Sprite *sprite, int x, int y) {
    if (sprite == NULL || sprite->map == NULL) {
        return 1;
    }

    return vg_draw_pixmap(sprite->map, sprite->width, sprite->height, x, y, 0x00B140);
}

int getWidth(Sprite *sprite) { return sprite->width; }

int getHeight(Sprite *sprite) { return sprite->height; }
