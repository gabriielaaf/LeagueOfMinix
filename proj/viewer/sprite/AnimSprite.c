#include "AnimSprite.h"

struct AnimSprite {
    int x;
    int y;

    int currentSprite;
    int currentTime;
    int animationTime;
    int numSprites;
    int looped;

    Sprite **sprites;
};

AnimSprite *createAnimSprite(int animationTime, int numSprites, int x, int y, Sprite **sprites) {
    if (animationTime <= 0 || numSprites <= 0 || sprites == NULL) {
        return NULL;
    }

    AnimSprite *animSprite = malloc(sizeof(AnimSprite));

    if (animSprite == NULL) {
        return NULL;
    }

    animSprite->currentSprite = 0;
    animSprite->currentTime = 0;
    animSprite->animationTime = animationTime;
    animSprite->numSprites = numSprites;
    animSprite->x = x;
    animSprite->y = y;
    animSprite->sprites = sprites;

    return animSprite;
}

void destroyAnimSprite(AnimSprite *animSprite) {
    if (animSprite == NULL) {
        return;
    }

    if (animSprite->sprites != NULL) {
        for (int i = 0; i < animSprite->numSprites; i++) {
            spriteDestroy(animSprite->sprites[i]);
        }
    }

    free(animSprite);
}

void updateAnimSprite(AnimSprite *animSprite) {
    if (animSprite == NULL) {
        return;
    }

    animSprite->currentTime++;

    if (animSprite->currentTime >= animSprite->animationTime) {
        animSprite->currentTime = 0;
        animSprite->currentSprite = (animSprite->currentSprite + 1) % animSprite->numSprites;
        if (animSprite->currentSprite == 0) {
            animSprite->looped = 1;
        }
    }
}

int drawAnimSprite(AnimSprite *animSprite) {
    if (animSprite == NULL || animSprite->sprites == NULL) {
        return 1;
    }

    return spriteDraw(
        animSprite->sprites[animSprite->currentSprite],
        animSprite->x,
        animSprite->y
    );
}

void moveAnimSprite(AnimSprite *animSprite, int dx, int dy) {
    if (animSprite == NULL) {
        return;
    }

    animSprite->x += dx;
    animSprite->y += dy;
}

void setAnimSpritePosition(AnimSprite *animSprite, int x, int y) {
    if (animSprite == NULL) {
        return;
    }

    animSprite->x = x;
    animSprite->y = y;
}

void animSpriteReset(AnimSprite *animSprite) {
    if (animSprite == NULL) return;
    animSprite->currentSprite = 0;
    animSprite->currentTime = 0;
    animSprite->looped = 0;
}

int animSpriteHasLooped(AnimSprite *animSprite) {
    if (animSprite == NULL || !animSprite->looped) return 0;
    animSprite->looped = 0;
    return 1;
}

Sprite *getCurrentSprite(AnimSprite *animSprite) { return animSprite->sprites[animSprite->currentSprite]; }
