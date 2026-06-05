#include "GameViewer.h"
#include "sprite/BuildSprites.h"
#include "../assets/minion_p1/minion_p1_xpms.h"
#include "../assets/minion_p2/minion_p2_xpms.h"
#include "../assets/tower_p1_xpm.h"
#include "../assets/tower_p2_xpm.h"

#include <stdlib.h>
#include <stdio.h>

GameViewer *gameViewerCreate() {
    printf("[GAMEVIEWER] gameViewerCreate START\n");
    fflush(stdout);

    GameViewer *gv = malloc(sizeof(GameViewer));

    printf("[GAMEVIEWER] malloc gv = %p\n", gv);
    fflush(stdout);

    if (!gv) return NULL;

    gv->p1 = NULL;
    gv->p2 = NULL;
    gv->minion_blue = NULL;
    gv->minion_red = NULL;
    gv->tower = NULL;

    printf("[GAMEVIEWER] before buildAnimations(1)\n");
    fflush(stdout);

    AnimSprite **anim1 = buildAnimations(1);

    printf("[GAMEVIEWER] after buildAnimations(1): anim1 = %p\n", anim1);
    fflush(stdout);

    printf("[GAMEVIEWER] before buildAnimations(2)\n");
    fflush(stdout);

    AnimSprite **anim2 = buildAnimations(2);

    printf("[GAMEVIEWER] after buildAnimations(2): anim2 = %p\n", anim2);
    fflush(stdout);

    if (!anim1 || !anim2) {
        printf("[GAMEVIEWER ERROR] buildAnimations failed\n");
        fflush(stdout);

        if (anim1) {
            for (int i = 0; i < NUM_ANIMS; i++) {
                if (anim1[i]) destroyAnimSprite(anim1[i]);
            }
            free(anim1);
        }

        if (anim2) {
            for (int i = 0; i < NUM_ANIMS; i++) {
                if (anim2[i]) destroyAnimSprite(anim2[i]);
            }
            free(anim2);
        }

        free(gv);
        return NULL;
    }

    printf("[GAMEVIEWER] before createChampionViewer p1\n");
    fflush(stdout);

    gv->p1 = createChampionViewer(anim1, NUM_ANIMS);

    printf("[GAMEVIEWER] after createChampionViewer p1: p1 = %p\n", gv->p1);
    fflush(stdout);

    printf("[GAMEVIEWER] before createChampionViewer p2\n");
    fflush(stdout);

    gv->p2 = createChampionViewer(anim2, NUM_ANIMS);

    printf("[GAMEVIEWER] after createChampionViewer p2: p2 = %p\n", gv->p2);
    fflush(stdout);

    printf("[GAMEVIEWER] before createMinionViewer blue\n");
    fflush(stdout);

    gv->minion_blue = createMinionViewer(
        (xpm_row_t *) minion_p1_stop,
        (xpm_row_t *) minion_p1_attack
    );

    printf("[GAMEVIEWER] after createMinionViewer blue: minion_blue = %p\n", gv->minion_blue);
    fflush(stdout);

    printf("[GAMEVIEWER] before createMinionViewer red\n");
    fflush(stdout);

    gv->minion_red = createMinionViewer(
        (xpm_row_t *) minion_p2_stop,
        (xpm_row_t *) minion_p2_attack
    );

    printf("[GAMEVIEWER] after createMinionViewer red: minion_red = %p\n", gv->minion_red);
    fflush(stdout);

    printf("[GAMEVIEWER] before createTowerViewer\n");
    fflush(stdout);

    gv->tower = createTowerViewer(
        (xpm_map_t) blue_tower_xpm,
        (xpm_map_t) red_tower_xpm
    );

    printf("[GAMEVIEWER] after createTowerViewer: tower = %p\n", gv->tower);
    fflush(stdout);

    if (!gv->p1 || !gv->p2 || !gv->minion_blue || !gv->minion_red || !gv->tower) {
        printf("[GAMEVIEWER ERROR] one viewer returned NULL\n");
        fflush(stdout);

        gameViewerDestroy(gv);
        return NULL;
    }

    printf("[GAMEVIEWER] gameViewerCreate END OK\n");
    fflush(stdout);

    return gv;
}

void gameViewerDestroy(GameViewer *gv) {
    if (!gv) return;

    if (gv->p1) destroyChampionViewer(gv->p1);
    if (gv->p2) destroyChampionViewer(gv->p2);
    if (gv->minion_blue) destroyMinionViewer(gv->minion_blue);
    if (gv->minion_red) destroyMinionViewer(gv->minion_red);
    if (gv->tower) destroyTowerViewer(gv->tower);

    free(gv);
}

void gameViewerUpdate(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions,
                      bool *p1_looped, bool *p2_looped) {
    if (!gv || !p1 || !p2 || !minions) return;

    *p1_looped = championViewerUpdate(gv->p1, p1);
    *p2_looped = championViewerUpdate(gv->p2, p2);

    minionViewerUpdate(gv->minion_blue);
    minionViewerUpdate(gv->minion_red);
}

void gameViewerDraw(GameViewer *gv, Champion *p1, Champion *p2, Minions *minions, Towers *towers) {
    if (!gv || !p1 || !p2 || !minions || !towers) return;

    towerViewerDraw(gv->tower, towers);
    minionViewerDraw(gv->minion_blue, minions, TEAM_BLUE);
    minionViewerDraw(gv->minion_red, minions, TEAM_RED);
    championDraw(gv->p1, p1);
    championDraw(gv->p2, p2);
}
