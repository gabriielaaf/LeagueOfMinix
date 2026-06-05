#include "ShopState.h"

#define SCREEN_WIDTH 1024

#define SHOP_BAR_W 300
#define BUY_BUTTON_W 80
#define BUY_BUTTON_GAP 15
#define SHOP_TOTAL_W (SHOP_BAR_W + BUY_BUTTON_GAP + BUY_BUTTON_W)

#define PLAYER1_SHOP_X 40
#define PLAYER2_SHOP_X (SCREEN_WIDTH - 40 - SHOP_TOTAL_W)

#define SHOP_ATTACK_Y 520
#define SHOP_SPEED_Y  585
#define SHOP_HP_Y     650

static PlayerShopState *playerShopStateCreate(int x) {
    PlayerShopState *playerShop = malloc(sizeof(PlayerShopState));
    if (!playerShop) return NULL;

    playerShop->attackBar = NULL;
    playerShop->speedBar  = NULL;
    playerShop->hpBar     = NULL;

    playerShop->attackBar = shopBarStateCreate(x, SHOP_ATTACK_Y, UPGRADE_DAMAGE);
    if (!playerShop->attackBar) {
        free(playerShop);
        return NULL;
    }

    playerShop->speedBar = shopBarStateCreate(x, SHOP_SPEED_Y, UPGRADE_SPEED);
    if (!playerShop->speedBar) {
        shopBarStateDestroy(playerShop->attackBar);
        free(playerShop);
        return NULL;
    }

    playerShop->hpBar = shopBarStateCreate(x, SHOP_HP_Y, UPGRADE_HP);
    if (!playerShop->hpBar) {
        shopBarStateDestroy(playerShop->attackBar);
        shopBarStateDestroy(playerShop->speedBar);
        free(playerShop);
        return NULL;
    }

    return playerShop;
}

static void playerShopStateDestroy(PlayerShopState *playerShop) {
    if (!playerShop) return;

    if (playerShop->attackBar) shopBarStateDestroy(playerShop->attackBar);
    if (playerShop->speedBar)  shopBarStateDestroy(playerShop->speedBar);
    if (playerShop->hpBar)     shopBarStateDestroy(playerShop->hpBar);

    free(playerShop);
}

static void playerShopStateResetClicks(PlayerShopState *playerShop) {
    if (!playerShop) return;

    if (playerShop->attackBar) shopBarStateResetClick(playerShop->attackBar);
    if (playerShop->speedBar)  shopBarStateResetClick(playerShop->speedBar);
    if (playerShop->hpBar)     shopBarStateResetClick(playerShop->hpBar);
}

ShopState *shopStateCreate(int player1X,
                           int player2X,
                           int attackY,
                           int speedY,
                           int hpY,
                           int barWidth,
                           int barHeight,
                           int buyButtonWidth,
                           int buyButtonHeight,
                           int buyButtonGap) {
    ShopState *shop = malloc(sizeof(ShopState));
    if (!shop) return NULL;

    shop->player1Shop = NULL;
    shop->player2Shop = NULL;

    shop->player1Shop = playerShopStateCreate(PLAYER1_SHOP_X);
    if (!shop->player1Shop) {
        shopStateDestroy(shop);
        return NULL;
    }

    shop->player2Shop = playerShopStateCreate(PLAYER2_SHOP_X);
    if (!shop->player2Shop) {
        shopStateDestroy(shop);
        return NULL;
    }

    return shop;
}

void shopStateDestroy(ShopState *shop) {
    if (!shop) return;

    if (shop->player1Shop) playerShopStateDestroy(shop->player1Shop);
    if (shop->player2Shop) playerShopStateDestroy(shop->player2Shop);

    free(shop);
}

void shopStateResetClicks(ShopState *shop) {
    if (!shop) return;

    playerShopStateResetClicks(shop->player1Shop);
    playerShopStateResetClicks(shop->player2Shop);
}
