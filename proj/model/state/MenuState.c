#include "MenuState.h"
#include <stdlib.h>

MenuState *menuStateCreate() {
    MenuState *menu = malloc(sizeof(MenuState));
    if (!menu) return NULL;

    menu->play_clicked = false;
    return menu;
}

void menuStateDestroy(MenuState *menu) {
    free(menu);
}

void menuStateStep(MenuState *menu, KeyboardState *kbd, MouseState *mouse) {
    (void)mouse;

    if (!menu || !kbd) return;

    menu->play_clicked = false;

    // Temporário: carregar em W começa o jogo
    if (kbd->p1.up) {
        menu->play_clicked = true;
    }
}

bool menuStateShouldStart(MenuState *menu) {
    return menu && menu->play_clicked;
}

void menuStateReset(MenuState *menu) {
    if (!menu) return;
    menu->play_clicked = false;
}
