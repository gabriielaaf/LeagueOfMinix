#ifndef VIEWER_H
#define VIEWER_H

#include "../model/game_state.h"

typedef struct {
    /*
     * Sprite *menu_background;
     * Sprite *arena_background;
     * Sprite *cursor;
     */
    int dummy;
} Viewer;

void viewer_init(Viewer *viewer);
void viewer_draw(Viewer *viewer, GameState *game_state);
void viewer_destroy(Viewer *viewer);

#endif