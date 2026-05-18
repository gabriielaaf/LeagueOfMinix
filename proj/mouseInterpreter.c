#include "mouseInterpreter.h"

#include <stdlib.h>

void mouse_state_init(MouseState *state, int x, int y) {
    if (state == NULL) {
        return;
    }

    state->x = x;
    state->y = y;

    state->p1.attack = false;
    state->p1.attack_pressed = false;

    state->p2.attack = false;
    state->p2.attack_pressed = false;
}

void mouse_interpret_packet(MouseState *state, struct packet *packet) {
    if (state == NULL || packet == NULL) {
        return;
    }

    /*
     * Mouse delta_y is positive when moving up,
     * but screen y increases downwards.
     */
    state->x += packet->delta_x;
    state->y -= packet->delta_y;

    /*
     * Left click -> Player 1 attack
     */
    if (packet->lb && !state->p1.attack_pressed) {
        state->p1.attack = true;
    }

    state->p1.attack_pressed = packet->lb;

    /*
     * Right click -> Player 2 attack
     */
    if (packet->rb && !state->p2.attack_pressed) {
        state->p2.attack = true;
    }

    state->p2.attack_pressed = packet->rb;
}

void mouse_clear_events(MouseState *state) {
    if (state == NULL) {
        return;
    }

    /*
     * Clear one-frame events only.
     * Keep attack_pressed because that represents holding the button.
     */
    state->p1.attack = false;
    state->p2.attack = false;
}