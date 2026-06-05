
#pragma once

#include "../model/state/State.h"

#include "sprite/Sprite.h"
#include "GameViewer.h"
#include "MenuViewer.h"
#include "ShopViewer.h"
#include "GameOverViewer.h"

typedef enum {
    BG_NONE = -1,
    BG_ARENA,
    BG_MENU,
    BG_SHOP,
    BG_GAME_OVER_BLUE,
    BG_GAME_OVER_RED
} BackgroundType;

typedef struct {
    Sprite *cursor;

    Sprite *currentBackground;
    BackgroundType loadedBackground;

    GameViewer *gameViewer;
    MenuViewer *menuViewer;
    ShopViewer *shopViewer;
    GameOverViewer *gameOverViewer;
} Viewer;

Viewer *viewerCreate();
void viewerDestroy(Viewer *v);

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y);
