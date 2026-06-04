#pragma once

#include "../model/state/shopBarState.h"

typedef struct {
    int dummy;
} ShopBarViewer;

ShopBarViewer *shopBarViewerCreate();
void shopBarViewerDestroy(ShopBarViewer *viewer);

void shopBarViewerDraw(ShopBarViewer *viewer, ShopBarState *bar);
