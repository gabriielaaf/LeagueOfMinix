

#include "Viewer.h"

#include "../assets/cursor/cursor_xpms.h"
#include "../assets/arena.h"
#include "../assets/home.h"
#include "../assets/p1_lose_xpm.h"
#include "../assets/p2_lose_xpm.h"
#include "../assets/shop_xpm.h"
#include "video.h"

#include <stdlib.h>

Viewer *viewerCreate() {
    Viewer *v = malloc(sizeof(Viewer));
    if (!v) return NULL;

    v->cursor = NULL;
    v->arenaBackground = NULL;
    v->menuBackground = NULL;
    v->shopBackground = NULL;
    v->gameOverBlueBackground = NULL;
    v->gameOverRedBackground = NULL;
    v->gameViewer = NULL;
    v->menuViewer = NULL;
    v->shopViewer = NULL;
    v->gameOverViewer = NULL;

    v->cursor = spriteCreate((xpm_map_t) cursor_xpm);
    if (!v->cursor) { viewerDestroy(v); return NULL; }

    v->arenaBackground = spriteCreate((xpm_map_t) background_xpm);
    if (!v->arenaBackground) { viewerDestroy(v); return NULL; }

    v->menuBackground = spriteCreate((xpm_map_t) home_xpm);
    if (!v->menuBackground) { viewerDestroy(v); return NULL; }

    v->shopBackground = spriteCreate((xpm_map_t) shop_xpm);
    if (!v->shopBackground) { viewerDestroy(v); return NULL; }

    v->gameOverBlueBackground = spriteCreate((xpm_map_t)p1_lose_xpm);
    if (!v->gameOverBlueBackground) { viewerDestroy(v); return NULL; }

    v->gameOverRedBackground = spriteCreate((xpm_map_t) p2_lose_xpm);
    if (!v->gameOverRedBackground) { viewerDestroy(v); return NULL; }

    v->gameViewer = gameViewerCreate();
    if (!v->gameViewer) { viewerDestroy(v); return NULL; }

    v->menuViewer = menuViewerCreate();
    if (!v->menuViewer) { viewerDestroy(v); return NULL; }

    v->shopViewer = shopViewerCreate();
    if (!v->shopViewer) { viewerDestroy(v); return NULL; }

    v->gameOverViewer = gameOverViewerCreate();
    if (!v->gameOverViewer) { viewerDestroy(v); return NULL; }

    return v;
}

void viewerDestroy(Viewer *v) {
    if (!v) return;

    if (v->cursor) spriteDestroy(v->cursor);
    if (v->arenaBackground) spriteDestroy(v->arenaBackground);
    if (v->menuBackground) spriteDestroy(v->menuBackground);
    if (v->shopBackground) spriteDestroy(v->shopBackground);
    if (v->gameOverBlueBackground) spriteDestroy(v->gameOverBlueBackground);
    if (v->gameOverRedBackground) spriteDestroy(v->gameOverRedBackground);
    if (v->gameViewer) gameViewerDestroy(v->gameViewer);
    if (v->menuViewer) menuViewerDestroy(v->menuViewer);
    if (v->shopViewer) shopViewerDestroy(v->shopViewer);
    if (v->gameOverViewer) gameOverViewerDestroy(v->gameOverViewer);

    free(v);
}

static const uint8_t *viewerGetBackground(Viewer *v, State *state) {
    if (!v || !state) return NULL;

    switch (state->state) {
        case STATE_MENU:
            return spriteGetMap(v->menuBackground);

        case STATE_PLAYING:
            return spriteGetMap(v->arenaBackground);

        case STATE_PAUSED:
            return spriteGetMap(v->arenaBackground);

        case STATE_GAME_OVER:
            if (state->winner == TEAM_BLUE) {
                return spriteGetMap(v->gameOverBlueBackground);
            }
            else if (state->winner == TEAM_RED) {
                return spriteGetMap(v->gameOverRedBackground);
            }
            return NULL;

        default:
            return NULL;
    }
}

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y) {
    if (!v || !state) return;

    video_clear_back_buffer(viewerGetBackground(v, state));

    switch (state->state) {
        case STATE_MENU:
            if (state->menu) {
                menuViewerDraw(v->menuViewer, state->menu);
            }
            break;

        case STATE_PLAYING:
            if (state->game) {
                gameViewerDraw(
                    v->gameViewer,
                    state->game->p1,
                    state->game->p2,
                    &state->game->minions,
                    &state->game->towers
                );
            }
            break;

        case STATE_PAUSED:
            if (state->game) {
                gameViewerDraw(
                    v->gameViewer,
                    state->game->p1,
                    state->game->p2,
                    &state->game->minions,
                    &state->game->towers
                );
            }

            if (state->shop) {
                shopViewerDraw(v->shopViewer, state->shop);
            }

            break;

        case STATE_GAME_OVER:
            gameOverViewerDraw(v->gameOverViewer, state);
            break;
    }

    if (state->state != STATE_PLAYING) {
        spriteDraw(v->cursor, cursor_x, cursor_y);
    }

    video_swap_buffers();
}
