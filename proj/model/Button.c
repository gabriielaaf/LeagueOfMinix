#include "Button.h"

ButtonState *buttonStateCreate(int x, int y, int width, int height) {
    ButtonState *button = malloc(sizeof(ButtonState));
    if (!button) return NULL;

    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;

    button->hovered = false;
    button->clicked = false;

    return button;
}

void buttonStateDestroy(ButtonState *button) {
    if (!button) return;
    free(button);
}

bool buttonStateContains(ButtonState *button, int x, int y) {
    if (!button) return false;

    return x >= button->x &&
           x < button->x + button->width &&
           y >= button->y &&
           y < button->y + button->height;
}


void buttonStateResetClick(ButtonState *button) {
    if (!button) return;
    button->clicked = false;
}
