#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/State.h"
#include "keyboardInterpreter.h"
#include "mouseInterpreter.h"

typedef struct {
    State *game_state;
    KeyboardState *keyboard;
    MouseState *mouse;
} Controller;

void controller_init(
    Controller *controller,
    State *gameState,
    KeyboardState *keyboard,
    MouseState *mouse
    // e necessario adicionar todo sos objetios como cahmpions e minions
);



void controller_update(Controller *controller);

#endif