#include "ShopController.h"

static void playerShopControllerUpdate(ShopController *controller,
                                       PlayerShopState *playerShop,
                                       MouseState *mouse) {
    if (!controller || !playerShop || !mouse) return;

    if (playerShop->attackBar) {
        shopBarControllerUpdate(
            controller->barController,
            playerShop->attackBar,
            mouse->x,
            mouse->y,
            mouse->p1.attack_pressed
        );
    }

    if (playerShop->defenseBar) {
        shopBarControllerUpdate(
            controller->barController,
            playerShop->defenseBar,
            mouse->x,
            mouse->y,
            mouse->p1.attack_pressed
        );
    }

    if (playerShop->hpBar) {
        shopBarControllerUpdate(
            controller->barController,
            playerShop->hpBar,
            mouse->x,
            mouse->y,
            mouse->p1.attack_pressed
        );
    }
}

ShopController *shopControllerCreate() {
    ShopController *controller = malloc(sizeof(ShopController));
    if (!controller) return NULL;

    controller->barController = shopBarControllerCreate();

    if (!controller->barController) {
        free(controller);
        return NULL;
    }

    return controller;
}

void shopControllerDestroy(ShopController *controller) {
    if (!controller) return;

    if (controller->barController) {
        shopBarControllerDestroy(controller->barController);
    }

    free(controller);
}

void shopControllerUpdate(ShopController *controller, ShopState *shop, MouseState *mouse) {
    if (!controller || !shop || !mouse) return;

    playerShopControllerUpdate(controller, shop->player1Shop, mouse);
    playerShopControllerUpdate(controller, shop->player2Shop, mouse);
}

