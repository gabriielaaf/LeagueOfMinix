#pragma once

#include <stdbool.h>
#include "../../input/KeyboardInterpreter.h"
#include "../../input/MouseInterpreter.h"

typedef struct {
    bool play_clicked;
    bool quit;
} MenuState;

MenuState *menuStateCreate();
void menuStateDestroy(MenuState *menu);

void menuStateStep(MenuState *menu, KeyboardState *kbd, MouseState *mouse);
bool menuStateShouldStart(MenuState *menu);
void menuStateReset(MenuState *menu);
