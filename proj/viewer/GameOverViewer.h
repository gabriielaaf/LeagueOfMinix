#pragma once

#include <stdlib.h>

#include "ButtonViewer.h"
#include "TextDrawer.h"

#include "../assets/menu/play_buttons_xpms.h"

#include "../model/state/State.h"

typedef struct {
    ButtonViewer *restartButtonViewer;
    ButtonViewer *quitButtonViewer;
} GameOverViewer;

GameOverViewer *gameOverViewerCreate();
void gameOverViewerDestroy(GameOverViewer *viewer);

void gameOverViewerDraw(GameOverViewer *viewer, State *state);
