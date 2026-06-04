#pragma once

#include "../model/state/MenuState.h"
#include "ButtonViewer.h"

typedef struct {
    ButtonViewer *playButtonViewer;
} MenuViewer;

MenuViewer *menuViewerCreate();
void menuViewerDestroy(MenuViewer *viewer);

void menuViewerDraw(MenuViewer *viewer, MenuState *menu);
