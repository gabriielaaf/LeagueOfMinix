#include "ButtonController.h"

void buttonControllerUpdate(ButtonState *button, MouseState *mouse) {
    if (!button || !mouse) return;

    button->hovered = buttonStateContains(button, mouse->x, mouse->y);

    if (button->hovered && mouse->p1.attack) {
        button->clicked = true;
    }
}
