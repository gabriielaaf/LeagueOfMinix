#pragma once

#include <stdbool.h>

typedef struct {
    bool play_clicked;
} MenuState;

MenuState *menuStateCreate();
void menuStateDestroy(MenuState *menu);

void menuStateSetPlayClicked(MenuState *menu, bool clicked);
bool menuStateShouldStart(MenuState *menu);
void menuStateReset(MenuState *menu);
