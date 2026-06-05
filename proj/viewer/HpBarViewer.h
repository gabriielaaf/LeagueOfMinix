#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "video.h"

#define HP_BAR_HEIGHT 6
#define HP_BAR_OFFSET 3

typedef struct {
    uint32_t high_color;
    uint32_t mid_color;
    uint32_t low_color;
    uint32_t empty_color;
    uint32_t border_color;
} HpBarViewer;

HpBarViewer *createHpBarViewer(void);
void destroyHpBarViewer(HpBarViewer *viewer);
void hpBarViewerDraw(HpBarViewer *viewer, int x, int y, int width, int current_hp, int max_hp);
