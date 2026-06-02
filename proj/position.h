#ifndef POSITION_H
#define POSITION_H

#include <math.h>

typedef struct {
    float x;
    float y;
} Position;

void position_move(Position *pos, int dx, int dy, float speed);

int position_px(Position pos);

int position_py(Position pos);

#endif
