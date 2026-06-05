#pragma once

#include "../model/state/State.h"
#include "ButtonViewer.h"

typedef struct {
    ButtonViewer *restartButtonViewer;
    ButtonViewer *quitButtonViewer;
} GameOverViewer;

GameOverViewer *gameOverViewerCreate();
void gameOverViewerDestroy(GameOverViewer *viewer);

void gameOverViewerDraw(GameOverViewer *viewer, State *state);