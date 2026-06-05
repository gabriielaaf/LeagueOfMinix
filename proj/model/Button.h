#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;

    bool hovered;
    bool clicked;
} ButtonState;

ButtonState *buttonStateCreate(int x, int y, int width, int height);
void buttonStateDestroy(ButtonState *button);

bool buttonStateContains(ButtonState *button, int x, int y);
void buttonStateResetClick(ButtonState *button);
