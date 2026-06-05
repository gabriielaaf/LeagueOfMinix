#pragma once

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

void mouseStateInit(MouseState *state, int x, int y);

void mouseInterpretPacket(MouseState *state, struct packet *packet, int screen_w, int screen_h);

void mouseClearEvents(MouseState *state);
