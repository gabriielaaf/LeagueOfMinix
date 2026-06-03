#pragma once

#include "stdbool.h"

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Box;

bool boxesOverlap(Box a, Box b);