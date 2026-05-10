#include <lcom/lcf.h>

#include "video.h"
#include "testsprite.h"
#include "sprite.h"

#define MODE_105 0x105

int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/proj/trace.txt");
    lcf_log_output("/home/lcom/labs/proj/output.txt");

    if (lcf_start(argc, argv)) {
        return 1;
    }

    lcf_cleanup();

    return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
  if (video_init_page_flipping(MODE_105) != 0) {
    return 1;
  }

  Sprite *sprite = sprite_create(test_sprite_xpm, 900, 300);

  if (sprite == NULL) {
    vg_exit();
    return 1;
  }

  int y = 300;
  int sprite_width = 16;

  for (int x = 900; x + sprite_width > 0; x -= 5) {
    sprite_set_position(sprite, x, y);

    video_clear_back_buffer(0);

    sprite_draw(sprite);

    video_swap_buffers();

    tickdelay(micros_to_ticks(16667));
  }

  wait_for_esc();

  sprite_destroy(sprite);

  vg_exit();

  return 0;
}

