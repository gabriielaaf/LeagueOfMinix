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

void menuStateSetPlayClicked(MenuState *menu, bool clicked) {
    if (!menu) return;

    menu->play_clicked = clicked;
}

bool menuStateShouldStart(MenuState *menu) {
    return menu && menu->play_clicked;
}

void menuStateReset(MenuState *menu) {
    if (!menu) return;

    menu->play_clicked = false;
}

