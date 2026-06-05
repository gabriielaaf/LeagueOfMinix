#pragma once

#include <stdlib.h>

#include "ButtonViewer.h"

#include "../assets/menu/play_buttons_xpms.h"

#include "../model/state/MenuState.h"

typedef struct {
    ButtonViewer *playButtonViewer;
} MenuViewer;

MenuViewer *menuViewerCreate();
void menuViewerDestroy(MenuViewer *viewer);

void menuViewerDraw(MenuViewer *viewer, MenuState *menu);
