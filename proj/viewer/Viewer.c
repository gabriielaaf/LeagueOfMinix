

#include "Viewer.h"

#include "../assets/cursor/cursor_xpms.h"
#include "../assets/arena.h"
#include "../assets/home.h"
#include "../assets/p1_lose_xpm.h"
#include "../assets/p2_lose_xpm.h"
#include "../assets/shop_xpm.h"
#include "video.h"

#include <stdlib.h>
#include <stdio.h>

static xpm_map_t backgroundXpm(BackgroundType type) {
    switch (type) {
        case BG_ARENA:          return (xpm_map_t) background_xpm;
        case BG_MENU:           return (xpm_map_t) home_xpm;
        case BG_SHOP:           return (xpm_map_t) shop_xpm;
        case BG_GAME_OVER_BLUE: return (xpm_map_t) p1_lose_xpm;
        case BG_GAME_OVER_RED:  return (xpm_map_t) p2_lose_xpm;
        default:                return NULL;
    }
}

static int viewerLoadBackground(Viewer *v, BackgroundType type) {
    if (v->loadedBackground == type) return 0;

    if (v->currentBackground) {
        spriteDestroy(v->currentBackground);
        v->currentBackground = NULL;
    }

    v->loadedBackground = BG_NONE;

    xpm_map_t xpm = backgroundXpm(type);
    if (!xpm) { printf("[BG] no xpm for type %d\n", type); fflush(stdout); return 1; }

    printf("[BG] loading background type %d\n", type); fflush(stdout);
    v->currentBackground = spriteCreate(xpm);
    if (!v->currentBackground) { printf("[BG ERROR] spriteCreate failed for type %d\n", type); fflush(stdout); return 1; }

    printf("[BG] loaded OK\n"); fflush(stdout);
    v->loadedBackground = type;
    return 0;
}

Viewer *viewerCreate() {
    Viewer *v = malloc(sizeof(Viewer));
    if (!v) return NULL;

    v->cursor = NULL;
    v->currentBackground = NULL;
    v->loadedBackground = BG_NONE;
    v->gameViewer = NULL;
    v->menuViewer = NULL;
    v->shopViewer = NULL;
    v->gameOverViewer = NULL;

    v->cursor = spriteCreate((xpm_map_t) cursor_xpm);
    if (!v->cursor) { viewerDestroy(v); return NULL; }

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
    if (v->currentBackground) spriteDestroy(v->currentBackground);
    if (v->gameViewer) gameViewerDestroy(v->gameViewer);
    if (v->menuViewer) menuViewerDestroy(v->menuViewer);
    if (v->shopViewer) shopViewerDestroy(v->shopViewer);
    if (v->gameOverViewer) gameOverViewerDestroy(v->gameOverViewer);

    free(v);
}

static const uint8_t *viewerGetBackground(Viewer *v, State *state) {
    if (!v || !state) return NULL;

    BackgroundType needed;

    switch (state->state) {
        case STATE_MENU:
            needed = BG_MENU;
            break;
        case STATE_PLAYING:
        case STATE_PAUSED:
            needed = BG_ARENA;
            break;
        case STATE_GAME_OVER:
            if (state->winner == TEAM_BLUE)      needed = BG_GAME_OVER_RED;
            else if (state->winner == TEAM_RED)  needed = BG_GAME_OVER_BLUE;
            else return NULL;
            break;
        default:
            return NULL;
    }

    if (viewerLoadBackground(v, needed) != 0) return NULL;
    return spriteGetMap(v->currentBackground);
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
