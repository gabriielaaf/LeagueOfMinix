#include "animSprite.h"

struct AnimSprite
{
    int currentSprite;
    int currentTime;
    int animationTime;
    int numSprites;
    Sprite **sprites;
};


AnimSprite *createAnimSprite(int animationTime, int numSprites, Sprite **sprites) {
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
    animSprite->sprites = sprites;

    return animSprite;
}



