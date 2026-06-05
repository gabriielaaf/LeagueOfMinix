#pragma once

#include <stdint.h>

void textDrawChar(char c,
                  int x,
                  int y,
                  uint32_t color,
                  uint8_t scale);

void textDrawString(const char *text,
                    int x,
                    int y,
                    uint32_t color,
                    uint8_t scale,
                    uint8_t spacing);

void textDrawInt(int value,
                 int x,
                 int y,
                 uint32_t color,
                 uint8_t scale,
                 uint8_t spacing);



