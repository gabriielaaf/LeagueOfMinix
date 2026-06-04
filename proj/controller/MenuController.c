#include "MenuController.h"

void menuControllerUpdate(MenuState *menu, KeyboardState *kbd, MouseState *mouse) {
    (void)mouse;

    if (!menu || !kbd) return;

    menu->play_clicked = false;

    // Temporary: W starts the game
    if (kbd->p1.up) {
        menu->play_clicked = true;
    }
}
