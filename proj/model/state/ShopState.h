#pragma once

#include "shopBarState.h"

typedef struct {
    ShopBarState *attackBar;
    ShopBarState *defenseBar;
    ShopBarState *hpBar;
} PlayerShopState;

typedef struct {
    PlayerShopState *player1Shop;
    PlayerShopState *player2Shop;
} ShopState;

ShopState *shopStateCreate(int player1X,
                           int player2X,
                           int attackY,
                           int defenseY,
                           int hpY,
                           int barWidth,
                           int barHeight,
                           int buyButtonWidth,
                           int buyButtonHeight,
                           int buyButtonGap);

void shopStateDestroy(ShopState *shop);

void shopStateResetClicks(ShopState *shop);
