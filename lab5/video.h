#ifndef VIDEO_H
#define VIDEO_H

#include "vbe.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

int vbe_set_mode(uint16_t mode);

int(set_vram_mapping)(uint16_t mode); 

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int(vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height,uint32_t color);

int wait_for_esc();

int vg_draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif
