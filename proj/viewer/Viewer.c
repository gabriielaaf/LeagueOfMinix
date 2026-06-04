#include "Viewer.h"

#include "../assets/cursor/cursor_xpms.h"
#include "video.h"

#include <stdlib.h>

Viewer *viewerCreate() {
    Viewer *v = malloc(sizeof(Viewer));
    if (!v) return NULL;

    v->cursor = NULL;
    v->gameViewer = NULL;
    v->menuViewer = NULL;

    v->cursor = spriteCreate((xpm_map_t) cursor_xpm);
    if (!v->cursor) {
        viewerDestroy(v);
        return NULL;
    }

    v->gameViewer = gameViewerCreate();
    if (!v->gameViewer) {
        viewerDestroy(v);
        return NULL;
    }

    v->menuViewer = menuViewerCreate();
    if (!v->menuViewer) {
        viewerDestroy(v);
        return NULL;
    }

    return v;
}

void viewerDestroy(Viewer *v) {
    if (!v) return;

    if (v->cursor) {
        spriteDestroy(v->cursor);
    }

    if (v->gameViewer) {
        gameViewerDestroy(v->gameViewer);
    }

    if (v->menuViewer) {
        menuViewerDestroy(v->menuViewer);
    }

    free(v);
}

void viewerDraw(Viewer *v, State *state, int cursor_x, int cursor_y) {
    if (!v || !state) return;

    video_clear_back_buffer(0);

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
            break;

        case STATE_GAME_OVER:
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
    }

    if (state->state != STATE_PLAYING)
        spriteDraw(v->cursor, cursor_x, cursor_y);

    video_swap_buffers();
}
