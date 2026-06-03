#include "Controller.h"
#include "vbe.h"

#include <lcom/lcf.h>
#include <stdlib.h>

Controller *controllerCreate() {
    Controller *ctrl = malloc(sizeof(Controller));
    if (!ctrl) return NULL;

    if (!stateInit(&ctrl->state)) {
        free(ctrl);
        return NULL;
    }

    ctrl->state.state = STATE_MENU;

    keyboardStateInit(&ctrl->kbd);
    mouseStateInit(&ctrl->mouse, MODE105_WIDTH / 2, MODE105_HEIGHT / 2);

    ctrl->viewer = viewerCreate();
    if (!ctrl->viewer) {
        stateDestroy(&ctrl->state);
        free(ctrl);
        return NULL;
    }

    return ctrl;
}

void controllerDestroy(Controller *ctrl) {
    if (!ctrl) return;

    stateDestroy(&ctrl->state);

    if (ctrl->viewer) {
        viewerDestroy(ctrl->viewer);
    }

    free(ctrl);
}

void controllerDraw(Controller *ctrl) {
    if (!ctrl) return;

    viewerDraw(
        ctrl->viewer,
        &ctrl->state,
        ctrl->state.game,
        ctrl->mouse.x,
        ctrl->mouse.y
    );
}
