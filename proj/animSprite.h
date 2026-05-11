#include "sprite.h"
#include <stdlib.h>

typedef struct AnimSprite AnimSprite;


AnimSprite *createAnimSprite(int animationTime, int numSprites, Sprite **sprites);

void destroyAnimSprite(AnimSprite *animSprite);

void updateAnimSprite(AnimSprite *animSprite);

int drawAnimSprite(AnimSprite *animSprite);

void moveAnimSprite(AnimSprite *animSprite, int dx, int dy);

void setAnimSpritePosition(AnimSprite *animSprite, int x, int y);
