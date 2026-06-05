#pragma once

#include <stdlib.h>

#include "../model/state/ShopState.h"

#include "shopBarViewer.h"

typedef struct {
    ShopBarViewer *barViewer;
} ShopViewer;

ShopViewer *shopViewerCreate();
void shopViewerDestroy(ShopViewer *viewer);

void shopViewerDraw(ShopViewer *viewer, ShopState *shop);
