#include <lcom/lcf.h>

#include "video.h"
#include "assets/yasuo_xpms.h"
#include "sprite.h"
#include "animSprite.h"
#include "champion.h"

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

    Sprite *front = sprite_create(yasuo_front_xpm);
    Sprite *southwest = sprite_create(yasuo_southwest_xpm);
    Sprite *left = sprite_create(yasuo_left_xpm);
    Sprite *northwest = sprite_create(yasuo_northwest_xpm);
    Sprite *up = sprite_create(yasuo_up_xpm);
    Sprite *northeast = sprite_create(yasuo_northeast_xpm);
    Sprite *right = sprite_create(yasuo_right_xpm);
    Sprite *southeast = sprite_create(yasuo_southeast_xpm);

    if (front == NULL || southwest == NULL || left == NULL || northwest == NULL ||
        up == NULL || northeast == NULL || right == NULL || southeast == NULL) {

        if (front != NULL) sprite_destroy(front);
        if (southwest != NULL) sprite_destroy(southwest);
        if (left != NULL) sprite_destroy(left);
        if (northwest != NULL) sprite_destroy(northwest);
        if (up != NULL) sprite_destroy(up);
        if (northeast != NULL) sprite_destroy(northeast);
        if (right != NULL) sprite_destroy(right);
        if (southeast != NULL) sprite_destroy(southeast);

        vg_exit();
        return 1;
    }

    Sprite *rotation_frames[] = {
        front,
        southwest,
        left,
        northwest,
        up,
        northeast,
        right,
        southeast
    };

    AnimSprite *rotation_anim = createAnimSprite(
        1,
        8,
        10,
        10,
        rotation_frames
    );

    if (rotation_anim == NULL) {
        sprite_destroy(front);
        sprite_destroy(southwest);
        sprite_destroy(left);
        sprite_destroy(northwest);
        sprite_destroy(up);
        sprite_destroy(northeast);
        sprite_destroy(right);
        sprite_destroy(southeast);

        vg_exit();
        return 1;
    }

    AnimSprite *animations[] = {
        rotation_anim
    };

    Champion *champion = create_champion(
        10,
        10,
        100,
        5,
        10,
        20,
        animations,
        1
    );

    if (champion == NULL) {
        destroyAnimSprite(rotation_anim);
        vg_exit();
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        champion_update(champion);

        video_clear_back_buffer(0);

        champion_draw(champion);

        video_swap_buffers();

        tickdelay(micros_to_ticks(16667));
    }

    wait_for_esc();

    destroy_champion(champion);

    vg_exit();

    return 0;
}

