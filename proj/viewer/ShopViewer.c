#include "ShopViewer.h"


#include <stdlib.h>

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

static void playerShopViewerDraw(ShopViewer *viewer, PlayerShopState *playerShop) {
    if (!viewer || !playerShop) return;

    if (playerShop->attackBar) {
        shopBarViewerDraw(viewer->barViewer, playerShop->attackBar);
    }

    if (playerShop->defenseBar) {
        shopBarViewerDraw(viewer->barViewer, playerShop->defenseBar);
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
