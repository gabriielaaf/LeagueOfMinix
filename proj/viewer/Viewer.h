#pragma once

#include "../model/state/State.h"

#include "sprite/Sprite.h"
#include "GameViewer.h"
#include "MenuViewer.h"

typedef struct {
    Sprite *cursor;

    GameViewer *gameViewer;
    MenuViewer *menuViewer;
} Viewer;

Viewer *viewerCreate();
void viewerDestroy(Viewer *v);

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y);
