#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "../assets/arena.h"
#include "../assets/cursor/cursor_xpms.h"
#include "../assets/home.h"
#include "../assets/p1_lose_xpm.h"
#include "../assets/p2_lose_xpm.h"
#include "../assets/shop_xpm.h"
#include "GameOverViewer.h"
#include "GameViewer.h"
#include "MenuViewer.h"
#include "ShopViewer.h"
#include "sprite/Sprite.h"
#include "video.h"

typedef struct {
    Sprite *cursor;

    Sprite *bgMenu;
    Sprite *bgArena;
    Sprite *bgShop;
    Sprite *bgGameOverBlue;
    Sprite *bgGameOverRed;

    GameViewer *gameViewer;
    MenuViewer *menuViewer;
    ShopViewer *shopViewer;
    GameOverViewer *gameOverViewer;
} Viewer;

Viewer *viewerCreate();
void viewerDestroy(Viewer *v);

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y);
