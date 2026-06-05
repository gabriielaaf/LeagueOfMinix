#pragma once

#include "../Button.h"

typedef struct {
    ButtonState *restartButton;
    ButtonState *quitButton;
} GameOverState;

GameOverState *gameOverStateCreate();
void gameOverStateDestroy(GameOverState *state);