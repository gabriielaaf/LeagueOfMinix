
#pragma once

#include "../model/state/State.h"

#include "sprite/Sprite.h"
#include "GameViewer.h"
#include "MenuViewer.h"
#include "ShopViewer.h"
#include "GameOverViewer.h"

typedef struct {
    Sprite *cursor;

    Sprite *arenaBackground;
    Sprite *menuBackground;
    Sprite *shopBackground;
    Sprite *gameOverBackground;

    GameViewer *gameViewer;
    MenuViewer *menuViewer;
    ShopViewer *shopViewer;
    GameOverViewer *gameOverViewer;
} Viewer;

Viewer *viewerCreate();
void viewerDestroy(Viewer *v);

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y);
