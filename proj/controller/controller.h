#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game_state.h"
#include "keyboardInterpreter.h"
#include "mouseInterpreter.h"

typedef struct {
    Game_state *game_state;
    KeyboardState *keyboard;
    MouseState *mouse;
} Controller;

void controller_init(
    Controller *controller,
    Game_state *game_state,
    KeyboardState *keyboard,
    MouseState *mouse
    // e necessario adicionar todo sos objetios como cahmpions e minions
);



void controller_update(Controller *controller);

#endif