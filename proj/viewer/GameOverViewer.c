#include "GameOverViewer.h"

#include "TextDrawer.h"
#include "../assets/menu/play_buttons_xpms.h" // temporário: button_xpm e button_hover_xpm

#include <stdlib.h>

#define COLOR_WHITE  0xFFFFFF
#define COLOR_RED    0xFF3333
#define COLOR_BLUE   0x3399FF
#define COLOR_GOLD   0xFFD700

GameOverViewer *gameOverViewerCreate() {
    GameOverViewer *viewer = malloc(sizeof(GameOverViewer));
    if (!viewer) return NULL;

    viewer->restartButtonViewer = NULL;
    viewer->quitButtonViewer = NULL;

    viewer->restartButtonViewer = buttonViewerCreate(
        (xpm_map_t) play_button_xpm,
        (xpm_map_t) play_button_hover_xpm
    );

    if (!viewer->restartButtonViewer) {
        gameOverViewerDestroy(viewer);
        return NULL;
    }

    viewer->quitButtonViewer = buttonViewerCreate(
        (xpm_map_t) button_xpm,
        (xpm_map_t) button_hover_xpm
    );

    if (!viewer->quitButtonViewer) {
        gameOverViewerDestroy(viewer);
        return NULL;
    }

    return viewer;
}

void gameOverViewerDestroy(GameOverViewer *viewer) {
    if (!viewer) return;

    if (viewer->restartButtonViewer) {
        buttonViewerDestroy(viewer->restartButtonViewer);
    }

    if (viewer->quitButtonViewer) {
        buttonViewerDestroy(viewer->quitButtonViewer);
    }

    free(viewer);
}

void gameOverViewerDraw(GameOverViewer *viewer, State *state) {
    if (!viewer || !state || !state->gameOver) return;

   
    buttonViewerDraw(viewer->restartButtonViewer, state->gameOver->restartButton);
    buttonViewerDraw(viewer->quitButtonViewer, state->gameOver->quitButton);

}