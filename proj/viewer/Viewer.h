#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "sprite/Sprite.h"
#include "GameViewer.h"
#include "MenuViewer.h"
#include "ShopViewer.h"
#include "GameOverViewer.h"

#include "../assets/cursor/cursor_xpms.h"
#include "../assets/arena.h"
#include "../assets/home.h"
#include "../assets/p1_lose_xpm.h"
#include "../assets/p2_lose_xpm.h"
#include "../assets/shop_xpm.h"

#include "../model/state/State.h"

#include "video.h"

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
