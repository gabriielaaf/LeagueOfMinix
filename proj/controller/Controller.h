#pragma once

#include "../model/state/State.h"
#include "../model/state/GameState.h"
#include "../viewer/Viewer.h"
#include "../input/KeyboardInterpreter.h"
#include "../input/MouseInterpreter.h"

typedef struct {
    State state;
    Viewer *viewer;
    KeyboardState kbd;
    MouseState mouse;
} Controller;

Controller *controllerCreate();
void controllerDestroy(Controller *ctrl);
void controllerUpdate(Controller *ctrl);
void controllerDraw(Controller *ctrl);
