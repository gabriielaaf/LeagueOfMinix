#pragma once

#include "../model/state/State.h"
#include "../model/state/GameState.h"
#include "sprite/Sprite.h"

typedef struct {
    Sprite *cursor;
} Viewer;

Viewer *viewerCreate();
void viewerDestroy(Viewer *v);
void viewerDraw(Viewer *v, State *state, GameState *gs, int cursor_x, int cursor_y);
