#pragma once

#include <stdbool.h>
#include "../Button.h"

#define SHOP_BAR_MAX_LEVEL 5

typedef struct {
    int x;
    int y;
    int width;
    int height;

    int level;

    ButtonState *buyButton;
} ShopBarState;

ShopBarState *shopBarStateCreate(int x, int y);
void shopBarStateDestroy(ShopBarState *bar);

void shopBarStateBuy(ShopBarState *bar);
bool shopBarStateIsMaxed(ShopBarState *bar);
void shopBarStateResetClick(ShopBarState *bar);