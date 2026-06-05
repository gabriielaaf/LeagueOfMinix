#pragma once

#include <stdlib.h>

#include "../model/state/shopBarState.h"

#include "video.h"

typedef struct {
    int dummy;
} ShopBarViewer;

ShopBarViewer *shopBarViewerCreate();
void shopBarViewerDestroy(ShopBarViewer *viewer);

void shopBarViewerDraw(ShopBarViewer *viewer, ShopBarState *bar);
