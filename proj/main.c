#include <lcom/lcf.h>

#include "video.h"

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

  video_clear_back_buffer(0);

  vg_draw_rectangle(100, 100, 300, 200, 14);

  video_swap_buffers();

  wait_for_esc();

  vg_exit();

  return 0;
}

