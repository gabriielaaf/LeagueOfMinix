#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "video.h"

/**
 * @brief Draws a single character to the back buffer.
 * Supported characters: uppercase A–Z, digits 0–9, and punctuation ! ? . : - + / ( ).
 * @param c Character to draw.
 * @param x Screen X coordinate of the top-left corner.
 * @param y Screen Y coordinate of the top-left corner.
 * @param color 32-bit ARGB colour.
 * @param scale Pixel scale factor (1 = original size).
 */
void textDrawChar(char c,
                  int x,
                  int y,
                  uint32_t color,
                  uint8_t scale);

/**
 * @brief Draws a null-terminated string to the back buffer.
 * @param text Null-terminated string to draw.
 * @param x Screen X coordinate of the first character's top-left corner.
 * @param y Screen Y coordinate of the first character's top-left corner.
 * @param color 32-bit ARGB colour.
 * @param scale Pixel scale factor (1 = original size).
 * @param spacing Extra pixels between characters.
 */
void textDrawString(const char *text,
                    int x,
                    int y,
                    uint32_t color,
                    uint8_t scale,
                    uint8_t spacing);

/**
 * @brief Draws a decimal integer to the back buffer.
 * @param value Integer value to render.
 * @param x Screen X coordinate of the first digit's top-left corner.
 * @param y Screen Y coordinate of the first digit's top-left corner.
 * @param color 32-bit ARGB colour.
 * @param scale Pixel scale factor (1 = original size).
 * @param spacing Extra pixels between digits.
 */
void textDrawInt(int value,
                 int x,
                 int y,
                 uint32_t color,
                 uint8_t scale,
                 uint8_t spacing);
