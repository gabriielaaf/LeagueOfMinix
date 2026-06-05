#include "GameOverViewer.h"

#include "TextDrawer.h"
#include "video.h"

#include <stdlib.h>

#define SCREEN_W 1024
#define SCREEN_H 768

#define COLOR_BLACK  0x000000
#define COLOR_WHITE  0xFFFFFF
#define COLOR_RED    0xFF3333
#define COLOR_BLUE   0x3399FF
#define COLOR_GOLD   0xFFD700

GameOverViewer *gameOverViewerCreate() {
    GameOverViewer *viewer = malloc(sizeof(GameOverViewer));
    if (!viewer) return NULL;

    viewer->dummy = 0;

    return viewer;
}

void gameOverViewerDestroy(GameOverViewer *viewer) {
    if (!viewer) return;

    free(viewer);
}

void gameOverViewerDraw(GameOverViewer *viewer, State *state) {
    if (!viewer || !state) return;

    vg_draw_rectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BLACK);

    textDrawString("GAME OVER", 340, 230, COLOR_RED, 5, 1);

    if (state->winner == 1) {
        textDrawString("PLAYER 1 WINS", 310, 340, COLOR_BLUE, 4, 1);
    }
    else if (state->winner == 2) {
        textDrawString("PLAYER 2 WINS", 310, 340, COLOR_GOLD, 4, 1);
    }
    else {
        textDrawString("NO WINNER", 365, 340, COLOR_WHITE, 4, 1);
    }

    textDrawString("PRESS ESC TO QUIT", 320, 470, COLOR_WHITE, 2, 1);
}
