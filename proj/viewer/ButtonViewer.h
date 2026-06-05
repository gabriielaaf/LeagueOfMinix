#pragma once

#include <lcom/lcf.h>
#include <stdlib.h>

#include "sprite/Sprite.h"

#include "../model/Button.h"

typedef struct {
    Sprite *normal;
    Sprite *hover;
} ButtonViewer;

ButtonViewer *buttonViewerCreate(xpm_map_t normal_xpm, xpm_map_t hover_xpm);
void buttonViewerDestroy(ButtonViewer *viewer);
void buttonViewerDraw(ButtonViewer *viewer, ButtonState *button);
