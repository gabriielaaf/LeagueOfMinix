#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "../model/state/ShopState.h"
#include "../input/MouseInterpreter.h"
#include "ShopBarController.h"

typedef struct {
    ShopBarController *barController;
} ShopController;

ShopController *shopControllerCreate();
void shopControllerDestroy(ShopController *controller);

void shopControllerUpdate(ShopController *controller, ShopState *shop, MouseState *mouse);
