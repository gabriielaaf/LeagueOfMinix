#include "shopBarViewer.h"

#include "video.h"

#include <stdlib.h>

#define BAR_BORDER_COLOR 7
#define BAR_EMPTY_COLOR 0
#define BAR_FILL_COLOR 6

#define BUY_COLOR 1
#define BUY_HOVER_COLOR 4
#define BUY_DISABLED_COLOR 8

ShopBarViewer *shopBarViewerCreate() {
    ShopBarViewer *viewer = malloc(sizeof(ShopBarViewer));
    if (!viewer) return NULL;

    viewer->dummy = 0;

    return viewer;
}

void shopBarViewerDestroy(ShopBarViewer *viewer) {
    if (!viewer) return;

    free(viewer);
}

void shopBarViewerDraw(ShopBarViewer *viewer, ShopBarState *bar) {
    if (!viewer || !bar || !bar->buyButton) return;

    int segmentWidth = bar->width / SHOP_BAR_MAX_LEVEL;

    vg_draw_rectangle(
        bar->x - 3,
        bar->y - 3,
        bar->width + 6,
        bar->height + 6,
        BAR_BORDER_COLOR
    );

    vg_draw_rectangle(
        bar->x,
        bar->y,
        bar->width,
        bar->height,
        BAR_EMPTY_COLOR
    );

    for (int i = 0; i < bar->level; i++) {
        vg_draw_rectangle(
            bar->x + i * segmentWidth + 2,
            bar->y + 2,
            segmentWidth - 4,
            bar->height - 4,
            BAR_FILL_COLOR
        );
    }

    uint32_t buyColor = BUY_COLOR;

    if (shopBarStateIsMaxed(bar)) {
        buyColor = BUY_DISABLED_COLOR;
    }
    else if (bar->buyButton->hovered) {
        buyColor = BUY_HOVER_COLOR;
    }

    vg_draw_rectangle(
        bar->buyButton->x - 3,
        bar->buyButton->y - 3,
        bar->buyButton->width + 6,
        bar->buyButton->height + 6,
        BAR_BORDER_COLOR
    );

    vg_draw_rectangle(
        bar->buyButton->x,
        bar->buyButton->y,
        bar->buyButton->width,
        bar->buyButton->height,
        buyColor
    );
}

