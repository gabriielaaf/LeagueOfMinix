#include "Controller.h"

#include "MenuController.h"
#include "GameController.h"

#include "vbe.h"

#include <lcom/lcf.h>
#include <stdlib.h>
#include <stdbool.h>

Controller *controllerCreate() {
    Controller *ctrl = malloc(sizeof(Controller));
    if (!ctrl) return NULL;

    ctrl->gameCtrl = NULL;
    ctrl->viewer = NULL;

    if (!stateInit(&ctrl->state)) {
        free(ctrl);
        return NULL;
    }

    ctrl->state.state = STATE_MENU;

    keyboardStateInit(&ctrl->kbd);
    mouseStateInit(&ctrl->mouse, MODE105_WIDTH / 2, MODE105_HEIGHT / 2);

    ctrl->gameCtrl = gameControllerCreate(MODE105_WIDTH, MODE105_HEIGHT);
    if (!ctrl->gameCtrl) {
        stateDestroy(&ctrl->state);
        free(ctrl);
        return NULL;
    }

    ctrl->viewer = viewerCreate();
    if (!ctrl->viewer) {
        gameControllerDestroy(ctrl->gameCtrl);
        stateDestroy(&ctrl->state);
        free(ctrl);
        return NULL;
    }

    return ctrl;
}

void controllerUpdate(Controller *ctrl, bool second_elapsed) {
    if (!ctrl) return;

    if (ctrl->kbd.exit) {
        gameQuit(&ctrl->state);
        return;
    }

    switch (ctrl->state.state) {
        case STATE_MENU:
            menuControllerUpdate(ctrl->state.menu, &ctrl->kbd, &ctrl->mouse);

            if (menuStateShouldStart(ctrl->state.menu)) {
                menuStateReset(ctrl->state.menu);
                gameStart(&ctrl->state);
            }

            break;

        case STATE_PLAYING: {
            bool p1_looped = false;
            bool p2_looped = false;

            gameViewerUpdate(
                ctrl->viewer->gameViewer,
                ctrl->state.game->p1,
                ctrl->state.game->p2,
                &ctrl->state.game->minions,
                &p1_looped,
                &p2_looped
            );

            gameControllerUpdate(
                ctrl->gameCtrl,
                ctrl->state.game->p1,
                ctrl->state.game->p2,
                &ctrl->state.game->minions,
                &ctrl->state.game->towers,
                &ctrl->kbd,
                &ctrl->mouse,
                second_elapsed,
                p1_looped,
                p2_looped
            );

            break;
        }

        case STATE_PAUSED:
            break;

        case STATE_GAME_OVER:
            break;
    }
}

void controllerDraw(Controller *ctrl) {
    if (!ctrl) return;

    viewerDraw(
        ctrl->viewer,
        &ctrl->state,
        ctrl->mouse.x,
        ctrl->mouse.y
    );
}

void controllerDestroy(Controller *ctrl) {
    if (!ctrl) return;

    if (ctrl->viewer) {
        viewerDestroy(ctrl->viewer);
    }

    if (ctrl->gameCtrl) {
        gameControllerDestroy(ctrl->gameCtrl);
    }

    stateDestroy(&ctrl->state);

    free(ctrl);
}
