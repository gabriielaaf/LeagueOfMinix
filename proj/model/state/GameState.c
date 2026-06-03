#include "GameState.h"
#include "../champion/ChampionConfig.h"
#include "../../controller/GameController.h"
#include "../../controller/MinionController.h"
#include "../../controller/ChampionController.h"
#include "../../viewer/GameViewer.h"

#include <lcom/lcf.h>
#include "vbe.h"
#include <stdlib.h>

GameState *gameStateCreate() {
    GameState *gs = malloc(sizeof(GameState));
    if (!gs) return NULL;

    gs->p1 = createChampion(BLUE_SPAWN, EAST, CHAMPION_W, CHAMPION_H);
    gs->p2 = createChampion(RED_SPAWN, WEST, CHAMPION_W, CHAMPION_H);
    if (!gs->p1 || !gs->p2) {
        if (gs->p1) destroyChampion(gs->p1);
        if (gs->p2) destroyChampion(gs->p2);
        free(gs);
        return NULL;
    }

    minionsInit(&gs->minions);
    minionsControllerInit(&gs->minions, MODE105_WIDTH);

    gs->ctrl = gameControllerCreate(MODE105_WIDTH, MODE105_HEIGHT);
    if (!gs->ctrl) {
        destroyChampion(gs->p1);
        destroyChampion(gs->p2);
        free(gs);
        return NULL;
    }

    gs->viewer = gameViewerCreate();
    if (!gs->viewer) {
        gameControllerDestroy(gs->ctrl);
        destroyChampion(gs->p1);
        destroyChampion(gs->p2);
        free(gs);
        return NULL;
    }

    return gs;
}

void gameStateDestroy(GameState *gs) {
    if (!gs) return;
    if (gs->viewer) gameViewerDestroy(gs->viewer);
    if (gs->ctrl) gameControllerDestroy(gs->ctrl);
    if (gs->p1) destroyChampion(gs->p1);
    if (gs->p2) destroyChampion(gs->p2);
    free(gs);
}

void gameStateStep(GameState *gs, KeyboardState *kbd, MouseState *mouse) {
    if (!gs) return;

    gameControllerUpdate(gs->ctrl, gs->p1, gs->p2, &gs->minions, kbd, mouse);

    bool p1_looped, p2_looped;
    gameViewerUpdate(gs->viewer, gs->p1, gs->p2, &gs->minions, &p1_looped, &p2_looped);

    championUpdate(gs->p1, p1_looped);
    championUpdate(gs->p2, p2_looped);
}

void gameStateDraw(GameState *gs) {
    if (!gs) return;
    gameViewerDraw(gs->viewer, gs->p1, gs->p2, &gs->minions);
}
