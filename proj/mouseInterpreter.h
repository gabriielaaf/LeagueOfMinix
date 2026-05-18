#ifndef MOUSE_INTERPRETER_H
#define MOUSE_INTERPRETER_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool attack;  // true só no momento em que o botão é pressionado
    bool attack_pressed; // botao a ser carregado
} PlayerMouseInput;

typedef struct {
    int x;
    int y;

    PlayerMouseInput p1;
    PlayerMouseInput p2;
} MouseState;

void mouse_state_init(MouseState *state, int x, int y);

void mouse_interpret_packet(MouseState *state, struct packet *packet);

void mouse_clear_events(MouseState *state);

#endif
