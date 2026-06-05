#include "ShopBarController.h"

ShopBarController *shopBarControllerCreate() {
    ShopBarController *controller = malloc(sizeof(ShopBarController));
    if (!controller) return NULL;

    controller->dummy = 0;

    return controller;
}

void shopBarControllerDestroy(ShopBarController *controller) {
    if (!controller) return;

    free(controller);
}

static bool isInsideButton(ButtonState *button, int mouse_x, int mouse_y) {
    if (!button) return false;

    return mouse_x >= button->x &&
           mouse_x < button->x + button->width &&
           mouse_y >= button->y &&
           mouse_y < button->y + button->height;
}

bool shopBarControllerUpdate(ShopBarController *controller,
                             ShopBarState *bar,
                             int mouse_x,
                             int mouse_y,
                             bool mouse_pressed) {
    if (!controller || !bar || !bar->buyButton) {
        return false;
    }

    ButtonState *buyButton = bar->buyButton;

    buyButton->hovered = isInsideButton(buyButton, mouse_x, mouse_y);

    if (buyButton->hovered && mouse_pressed && !shopBarStateIsMaxed(bar)) {
        buyButton->clicked = true;
        shopBarStateBuy(bar);
        return true;
    }

    buyButton->clicked = false;
    return false;
}