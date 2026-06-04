#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;

    bool clicked;
    bool hovered;

    uint32_t color;
    uint32_t hover_color;
    uint32_t border_color;
} Button;