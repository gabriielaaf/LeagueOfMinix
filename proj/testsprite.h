#ifndef XPMS_H
#define XPMS_H

#include <lcom/lcf.h>

/* Transparent = 255 */
/* Black = 0 */
/* Red = 4 */
/* Blue = 1 */
/* Green = 2 */
/* Yellow outline = 14 */

static xpm_row_t test_sprite_red_xpm[] = {
  "16 16 4",
  ". 255",
  "x 14",
  "o 0",
  "+ 4",
  "................",
  ".....xxxxxx.....",
  "...xxxxxxxxxx...",
  "..xxx++++++xxx..",
  ".xxx++++++++xxx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xx++++++++++xx.",
  ".xx++++++++++xx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xxx++++++++xxx.",
  "..xxx++++++xxx..",
  "...xxxxxxxxxx...",
  ".....xxxxxx.....",
  "................"
};

static xpm_row_t test_sprite_blue_xpm[] = {
  "16 16 4",
  ". 255",
  "x 14",
  "o 0",
  "+ 1",
  "................",
  ".....xxxxxx.....",
  "...xxxxxxxxxx...",
  "..xxx++++++xxx..",
  ".xxx++++++++xxx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xx++++++++++xx.",
  ".xx++++++++++xx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xxx++++++++xxx.",
  "..xxx++++++xxx..",
  "...xxxxxxxxxx...",
  ".....xxxxxx.....",
  "................"
};

static xpm_row_t test_sprite_green_xpm[] = {
  "16 16 4",
  ". 255",
  "x 14",
  "o 0",
  "+ 2",
  "................",
  ".....xxxxxx.....",
  "...xxxxxxxxxx...",
  "..xxx++++++xxx..",
  ".xxx++++++++xxx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xx++++++++++xx.",
  ".xx++++++++++xx.",
  ".xx+++oooo+++xx.",
  ".xx+++oooo+++xx.",
  ".xxx++++++++xxx.",
  "..xxx++++++xxx..",
  "...xxxxxxxxxx...",
  ".....xxxxxx.....",
  "................"
};

#endif
