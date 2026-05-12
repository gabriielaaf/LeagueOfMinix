#include <lcom/lcf.h>
#include <string.h>

#include "video.h"
#include "sprite.h"
#include "animSprite.h"
#include "champion.h"

#include "assets/yasuo_xpms.h"
#include "assets/gabiteste.h"

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
    /*
     * Run with:
     * lcom_run proj test
     *
     * This only tests gabi_test_xpm moving to the right.
     */
    if ((argc > 0 && strcmp(argv[0], "test") == 0) ||
        (argc > 1 && strcmp(argv[1], "test") == 0)) {

        if (video_init_page_flipping(0x105) != 0) {
            return 1;
        }

        Sprite *sprite = sprite_create(gabi_test_xpm);

        if (sprite == NULL) {
            vg_exit();
            return 1;
        }


        video_clear_back_buffer(0);

        sprite_draw(sprite, 300, 300);

        video_swap_buffers();


        

        wait_for_esc();

        sprite_destroy(sprite);

        vg_exit();

        return 0;
    }

    /*
     * Normal main: Yasuo attack animation.
     */
    if (video_init_page_flipping(0x105) != 0) {
        return 1;
    }

    Sprite *attack_up = sprite_create(yasuo_attack_up_xpm);
    Sprite *attack_mid = sprite_create(yasuo_attack_mid_xpm);
    Sprite *attack_down = sprite_create(yasuo_attack_down_xpm);

    if (attack_up == NULL || attack_mid == NULL || attack_down == NULL) {
        if (attack_up != NULL) sprite_destroy(attack_up);
        if (attack_mid != NULL) sprite_destroy(attack_mid);
        if (attack_down != NULL) sprite_destroy(attack_down);

        vg_exit();
        return 1;
    }

    Sprite *attack_frames[] = {
        attack_up,
        attack_mid,
        attack_down
    };

    AnimSprite *attack_anim = createAnimSprite(
        20,
        3,
        350,
        220,
        attack_frames
    );

    if (attack_anim == NULL) {
        sprite_destroy(attack_up);
        sprite_destroy(attack_mid);
        sprite_destroy(attack_down);

        vg_exit();
        return 1;
    }

    AnimSprite *animations[] = {
        attack_anim
    };

    Champion *champion = create_champion(
        350,
        220,
        100,
        5,
        10,
        20,
        animations,
        1
    );

    if (champion == NULL) {
        destroyAnimSprite(attack_anim);

        vg_exit();
        return 1;
    }

    for (int i = 0; i < 600; i++) {
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


