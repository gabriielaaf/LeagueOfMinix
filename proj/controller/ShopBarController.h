#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "../model/state/shopBarState.h"

typedef struct {
    int dummy;
} ShopBarController;

ShopBarController *shopBarControllerCreate();
void shopBarControllerDestroy(ShopBarController *controller);

bool shopBarControllerUpdate(ShopBarController *controller,ShopBarState *bar,int mouse_x,int mouse_y,bool mouse_pressed);