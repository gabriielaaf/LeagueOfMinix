#include <lcom/lcf.h>

#include "video.h"
#include "testsprite.h"
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

    /*
     * Animation 0:
     * red -> green -> blue
     */
    Sprite *red1 = sprite_create(test_sprite_red_xpm);
    Sprite *green1 = sprite_create(test_sprite_green_xpm);
    Sprite *blue1 = sprite_create(test_sprite_blue_xpm);

    if (red1 == NULL || green1 == NULL || blue1 == NULL) {
        if (red1 != NULL) sprite_destroy(red1);
        if (green1 != NULL) sprite_destroy(green1);
        if (blue1 != NULL) sprite_destroy(blue1);

        vg_exit();
        return 1;
    }

    Sprite *rgb_frames[] = {
        red1,
        green1,
        blue1
    };

    AnimSprite *rgb_anim = createAnimSprite(
        10,     // animationTime
        3,      // numSprites
        900,    // x
        300,    // y
        rgb_frames
    );

    if (rgb_anim == NULL) {
        sprite_destroy(red1);
        sprite_destroy(green1);
        sprite_destroy(blue1);

        vg_exit();
        return 1;
    }

    /*
     * Animation 1:
     * green -> blue
     *
     * Important:
     * Create new Sprite objects here.
     * Do NOT reuse green1/blue1, because destroyAnimSprite()
     * destroys its own sprites.
     */
    Sprite *green2 = sprite_create(test_sprite_green_xpm);
    Sprite *blue2 = sprite_create(test_sprite_blue_xpm);

    if (green2 == NULL || blue2 == NULL) {
        if (green2 != NULL) sprite_destroy(green2);
        if (blue2 != NULL) sprite_destroy(blue2);

        destroyAnimSprite(rgb_anim);

        vg_exit();
        return 1;
    }

    Sprite *gb_frames[] = {
        green2,
        blue2
    };

    AnimSprite *gb_anim = createAnimSprite(
        3,     // animationTime
        2,      // numSprites
        900,    // x
        300,    // y
        gb_frames
    );

    if (gb_anim == NULL) {
        destroyAnimSprite(rgb_anim);

        sprite_destroy(green2);
        sprite_destroy(blue2);

        vg_exit();
        return 1;
    }

    /*
     * Champion animations:
     * animations[0] = red -> green -> blue
     * animations[1] = green -> blue
     */
    AnimSprite *animations[] = {
        rgb_anim,
        gb_anim
    };

    Champion *champion = create_champion(
        900,    // x
        300,    // y
        100,    // hp
        5,      // speed
        10,     // attack damage
        20,     // ability damage
        animations,
        2       // number of animations
    );

    if (champion == NULL) {
        destroyAnimSprite(rgb_anim);
        destroyAnimSprite(gb_anim);

        vg_exit();
        return 1;
    }

    /*
     * Test:
     * - starts with red -> green -> blue
     * - after some frames switches to green -> blue
     * - moves left
     */
    for (int i = 0; i < 350; i++) {
        if (i == 150) {
            champion_set_animation(champion, 1);
        }

        moveChampion(champion, -2, 0);

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

