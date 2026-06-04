#include "Viewer.h"
#include "../assets/cursor/cursor_xpms.h"
#include "video.h"

#include <stdlib.h>

Viewer *viewerCreate() {
    Viewer *v = malloc(sizeof(Viewer));
    if (!v) return NULL;

    v->cursor = spriteCreate((xpm_map_t)cursor_xpm);
    if (!v->cursor) { free(v); return NULL; }

    return v;
}

void viewerDestroy(Viewer *v) {
    if (!v) return;
    if (v->cursor) spriteDestroy(v->cursor);
    free(v);
}

void viewerDraw(Viewer *v, State *state, GameState *gs, int cursor_x, int cursor_y) {
    if (!v) return;

    video_clear_back_buffer(0);

    switch (state->state) {
        case STATE_PLAYING:
            gameStateDraw(gs);
            break;
        default:
            break;
    }

    spriteDraw(v->cursor, cursor_x, cursor_y);
    video_swap_buffers();
}
