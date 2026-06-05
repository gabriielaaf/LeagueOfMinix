#pragma once

#include "../model/state/State.h"

typedef struct {
    int dummy;
} GameOverViewer;

GameOverViewer *gameOverViewerCreate();
void gameOverViewerDestroy(GameOverViewer *viewer);

void gameOverViewerDraw(GameOverViewer *viewer, State *state);
