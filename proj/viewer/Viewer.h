#ifndef VIEWER_H
#define VIEWER_H

#include "../model/State.h"

typedef struct {
    /*
     * Sprite *menu_background;
     * Sprite *arena_background;
     * Sprite *cursor;
     */
    int dummy;
} Viewer;

void viewerInit(Viewer *viewer);
void viewerDraw(Viewer *viewer, State *gameState);
void viewerDestroy(Viewer *viewer);

#endif