#pragma once

#include "../model/state/MenuState.h"
#include "../input/KeyboardInterpreter.h"
#include "../input/MouseInterpreter.h"
#include <model/state/MenuState.h>

void menuControllerUpdate(MenuState *menu, KeyboardState *kbd, MouseState *mouse);
