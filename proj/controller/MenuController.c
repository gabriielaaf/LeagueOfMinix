#include "MenuController.h"

void menuControllerUpdate(MenuState *menu, KeyboardState *kbd, MouseState *mouse) {
    (void)mouse;

    if (!menu || !kbd) return;

    menu->play_clicked = false;

    

    // Temporary: retangulo de exemplo
    if (mouse->x > 50 && mouse->x < 100 && mouse->y > 100 && mouse ->y < 300) {
        menu->play_clicked = true;
    }
}
