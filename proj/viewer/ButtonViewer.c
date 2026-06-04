#include "ButtonViewer.h"
#include "video.h"

#include <stdint.h>

static void drawFilledRect(int x, int y, int w, int h, uint32_t color) {
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            video_draw_pixel(x + col, y + row, color);
        }
    }
}

void buttonViewerDraw(Button *button) {
    if (!button) return;

    uint32_t body_color = button->hovered ? button->hover_color : button->color;

    drawFilledRect(
        button->x - 4,
        button->y - 4,
        button->w + 8,
        button->h + 8,
        button->border_color
    );

    drawFilledRect(
        button->x,
        button->y,
        button->w,
        button->h,
        body_color
    );
}