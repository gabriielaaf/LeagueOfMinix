#ifndef ANIM_SPRITE_H
#define ANIM_SPRITE_H


#include "Sprite.h"

typedef struct AnimSprite AnimSprite;

AnimSprite *createAnimSprite(int animationTime, int numSprites,int x, int y, Sprite **sprites);

void destroyAnimSprite(AnimSprite *animSprite);

void updateAnimSprite(AnimSprite *animSprite);

int drawAnimSprite(AnimSprite *animSprite);

void moveAnimSprite(AnimSprite *animSprite, int dx, int dy);

void setAnimSpritePosition(AnimSprite *animSprite, int x, int y);

void animSpriteReset(AnimSprite *animSprite);

int animSpriteHasLooped(AnimSprite *animSprite);

Sprite *getCurrentSprite(AnimSprite *animSprite);

#endif
