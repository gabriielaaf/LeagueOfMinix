#include "ButtonController.h"

void buttonControllerUpdate(ButtonState *button, MouseState *mouse) {
    if (!button || !mouse) return;

    button->hovered = buttonStateContains(button, mouse->x, mouse->y);

    button->clicked = false;

    if (button->hovered && mouse->p1.attack_pressed) {
        button->clicked = true;
    }
}

