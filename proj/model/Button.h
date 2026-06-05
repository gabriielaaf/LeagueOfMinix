#pragma once

#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;

    bool hovered;
    bool clicked;
} ButtonState;

ButtonState *buttonStateCreate();
void buttonStateDestroy(ButtonState *button);

void buttonStateSetPosition(ButtonState *button, int x, int y);
void buttonStateSetSize(ButtonState *button, int width, int height);

bool buttonStateContains(ButtonState *button, int x, int y);
void buttonStateResetClick(ButtonState *button);

