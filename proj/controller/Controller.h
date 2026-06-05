#pragma once

#include <lcom/lcf.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../model/state/State.h"
#include "../viewer/Viewer.h"

#include "../input/KeyboardInterpreter.h"
#include "../input/MouseInterpreter.h"

#include "GameController.h"
#include "MenuController.h"

#include "vbe.h"

typedef struct {
    State state;

    KeyboardState kbd;
    MouseState mouse;

    GameController *gameCtrl;
    Viewer *viewer;
} Controller;

Controller *controllerCreate();
void controllerDestroy(Controller *ctrl);

void controllerUpdate(Controller *ctrl, bool second_elapsed);
void controllerDraw(Controller *ctrl);
