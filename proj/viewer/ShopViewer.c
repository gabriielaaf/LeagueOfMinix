#include "ShopViewer.h"

ShopViewer *shopViewerCreate() {
    ShopViewer *viewer = malloc(sizeof(ShopViewer));
    if (!viewer) return NULL;

    viewer->barViewer = NULL;

    viewer->barViewer = shopBarViewerCreate();

    if (!viewer->barViewer) {
        shopViewerDestroy(viewer);
        return NULL;
    }

    return viewer;
}

void shopViewerDestroy(ShopViewer *viewer) {
    if (!viewer) return;

    if (viewer->barViewer) {
        shopBarViewerDestroy(viewer->barViewer);
    }

    free(viewer);
}

/**
 * @brief Draws all three upgrade bars for a single player's shop column.
 * @param viewer ShopViewer providing the bar renderer.
 * @param playerShop PlayerShopState containing the bars to draw.
 */
static void playerShopViewerDraw(ShopViewer *viewer, PlayerShopState *playerShop) {
    if (!viewer || !playerShop) return;

    if (playerShop->attackBar) {
        shopBarViewerDraw(viewer->barViewer, playerShop->attackBar);
    }

    if (playerShop->speedBar) {
        shopBarViewerDraw(viewer->barViewer, playerShop->speedBar);
    }

    if (playerShop->hpBar) {
        shopBarViewerDraw(viewer->barViewer, playerShop->hpBar);
    }
}

void shopViewerDraw(ShopViewer *viewer, ShopState *shop) {
    if (!viewer || !shop) return;

    playerShopViewerDraw(viewer, shop->player1Shop);
    playerShopViewerDraw(viewer, shop->player2Shop);
}
