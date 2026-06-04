#pragma once

#include <stdbool.h>
#include "../Button.h"

typedef struct {
    ButtonState *playButton;
} MenuState;

MenuState *menuStateCreate();
void menuStateDestroy(MenuState *menu);

bool menuStateShouldStart(MenuState *menu);
void menuStateReset(MenuState *menu);
