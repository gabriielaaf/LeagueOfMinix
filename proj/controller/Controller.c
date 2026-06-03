#include "Controller.h"
#include "vbe.h"

#include <lcom/lcf.h>
#include <stdlib.h>

Controller *controllerCreate() {
    Controller *ctrl = malloc(sizeof(Controller));
    if (!ctrl) return NULL;

    stateInit(&ctrl->state);
    gameStart(&ctrl->state);  // jump straight into game (no menu yet)

    keyboardStateInit(&ctrl->kbd);
    mouseStateInit(&ctrl->mouse, MODE105_WIDTH / 2, MODE105_HEIGHT / 2);

    ctrl->game = gameStateCreate();
    if (!ctrl->game) { free(ctrl); return NULL; }

    ctrl->viewer = viewerCreate();
    if (!ctrl->viewer) {
        gameStateDestroy(ctrl->game);
        free(ctrl);
        return NULL;
    }

    return ctrl;
}

void controllerDestroy(Controller *ctrl) {
    if (!ctrl) return;
    if (ctrl->game)   gameStateDestroy(ctrl->game);
    if (ctrl->viewer) viewerDestroy(ctrl->viewer);
    free(ctrl);
}

void controllerUpdate(Controller *ctrl) {
    if (!ctrl) return;

    if (ctrl->kbd.exit) {
        gameQuit(&ctrl->state);
        return;
    }

    switch (ctrl->state.state) {
        case STATE_PLAYING:
            gameStateStep(ctrl->game, &ctrl->kbd, &ctrl->mouse);
            break;
        default:
            break;
    }
}

void controllerDraw(Controller *ctrl) {
    if (!ctrl) return;
    viewerDraw(ctrl->viewer, &ctrl->state, ctrl->game, ctrl->mouse.x, ctrl->mouse.y);
}

void controllerStep(Controller *ctrl) {
    controllerUpdate(ctrl);
    controllerDraw(ctrl);
}
