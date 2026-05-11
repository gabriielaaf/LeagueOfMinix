#include <lcom/lcf.h>

#include "video.h"
#include "testsprite.h"
#include "sprite.h"
#include "animSprite.h"

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

    Sprite *red = sprite_create(test_sprite_red_xpm);
    Sprite *blue = sprite_create(test_sprite_blue_xpm);
    Sprite *green = sprite_create(test_sprite_green_xpm);

    if (red == NULL || blue == NULL || green == NULL) {
        if (red != NULL) sprite_destroy(red);
        if (blue != NULL) sprite_destroy(blue);
        if (green != NULL) sprite_destroy(green);

        vg_exit();
        return 1;
    }

    Sprite *frames[] = {
        red,
        blue,
        green
    };

    AnimSprite *anim = createAnimSprite(10, 3, 900, 300, frames);

    if (anim == NULL) {
        sprite_destroy(red);
        sprite_destroy(blue);
        sprite_destroy(green);

        vg_exit();
        return 1;
    }

    for (int x = 900; x + 16 > 0; x -= 5) {
        update_AnimSprite(anim);
        setAnimSpritePosition(anim, x, 300);

        video_clear_back_buffer(0);

        drawAnimSprite(anim);

        video_swap_buffers();

        tickdelay(micros_to_ticks(16667));
    }

    wait_for_esc();

    destroyAnimSprite(anim);

    vg_exit();

    return 0;
}

