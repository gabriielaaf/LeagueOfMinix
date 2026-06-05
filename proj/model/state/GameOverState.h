#pragma once

#include <stdlib.h>
#include "../Button.h"

typedef struct {
    ButtonState *restartButton;
    ButtonState *quitButton;
} GameOverState;

GameOverState *gameOverStateCreate();
void gameOverStateDestroy(GameOverState *state);
