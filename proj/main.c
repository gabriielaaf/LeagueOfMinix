#include <lcom/lcf.h>
#include <lcom/proj.h>
#include <lcom/timer.h>

#include <string.h>

#include "video.h"
#include "keyboard.h"
#include "keyboardInterpreter.h"

#include "sprite.h"
#include "animSprite.h"
#include "champion.h"


#include "assets/yasuo_xpms.h"
#include "assets/gabiteste.h"

#define CHAMPION_SPEED 5

void foo();

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
     * Normal main: Yasuo standing in 8 directions with WASD movement.
     * Animation indices match Direction enum: NORTH=0, SOUTH=1, EAST=2, WEST=3,
     * NORTHEAST=4, NORTHWEST=5, SOUTHEAST=6, SOUTHWEST=7
     */
    if (video_init_page_flipping(0x105) != 0) {
        return 1;
    }

    xpm_row_t *stop_xpms[8] = {
        yasuo_up_xpm,        /* NORTH      */
        yasuo_front_xpm,     /* SOUTH      */
        yasuo_right_xpm,     /* EAST       */
        yasuo_left_xpm,      /* WEST       */
        yasuo_northeast_xpm, /* NORTHEAST  */
        yasuo_northwest_xpm, /* NORTHWEST  */
        yasuo_southeast_xpm, /* SOUTHEAST  */
        yasuo_southwest_xpm, /* SOUTHWEST  */
    };

    AnimSprite *animations[8];
    int anims_created = 0;

    for (int i = 0; i < 8; i++) {
        Sprite *s = sprite_create(stop_xpms[i]);
        if (s == NULL) {
            for (int j = 0; j < anims_created; j++) destroyAnimSprite(animations[j]);
            vg_exit();
            return 1;
        }
        Sprite **frames = malloc(sizeof(Sprite *));
        if (frames == NULL) {
            sprite_destroy(s);
            for (int j = 0; j < anims_created; j++) destroyAnimSprite(animations[j]);
            vg_exit();
            return 1;
        }
        frames[0] = s;
        animations[i] = createAnimSprite(1, 1, 350, 220, frames);
        if (animations[i] == NULL) {
            free(frames);
            sprite_destroy(s);
            for (int j = 0; j < anims_created; j++) destroyAnimSprite(animations[j]);
            vg_exit();
            return 1;
        }
        anims_created++;
    }

    Champion *champion = create_champion(350, 220, animations, 8);

    if (champion == NULL) {
        for (int i = 0; i < 8; i++) destroyAnimSprite(animations[i]);
        vg_exit();
        return 1;
    }

    foo(); // NÃO REMOVER, O ZÉ EXPLICA O PQ E DEPOIS RESOLVE

    uint8_t timer_bit_no;
    if (timer_subscribe_int(&timer_bit_no) != 0) {
        destroy_champion(champion);
        vg_exit();
        return 1;
    }
    timer_set_frequency(0, 60);

    uint8_t kbd_bit_no;
    if (kbd_subscribe_int(&kbd_bit_no) != 0) {
        timer_unsubscribe_int();
        destroy_champion(champion);
        vg_exit();
        return 1;
    }

    uint32_t timer_irq_set = BIT(timer_bit_no);
    uint32_t kbd_irq_set = BIT(kbd_bit_no);

    KeyboardState kstate;
    keyboard_state_init(&kstate);

    int r, ipc_status;
    message msg;

    int counter = 0;
    while (!kstate.exit) {
      if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
        printf("driver_receive failed: %d\n", r);
        continue;
      }

      if (!is_ipc_notify(ipc_status))
        continue;

      switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE:
        if (msg.m_notify.interrupts & kbd_irq_set) {
          kbd_ih();
          if (kbd_error) {
            kbd_error = false;
            reset_scancode();
            break;
          }
          if (scancode_complete()) {
            keyboard_interpret_scancode(&kstate, get_scancode_bytes(),
                                        get_scancode_size());
            reset_scancode();
          }
        }

        if (msg.m_notify.interrupts & timer_irq_set) {
          timer_int_handler();
          counter++;
          if (counter == 3) {
            counter = 0;
            int dx = 0, dy = 0;
            if (kstate.p1.left)
              dx -= CHAMPION_SPEED;
            if (kstate.p1.right)
              dx += CHAMPION_SPEED;
            if (kstate.p1.up)
              dy -= CHAMPION_SPEED;
            if (kstate.p1.down)
              dy += CHAMPION_SPEED;
            moveChampion(champion, dx, dy);

            champion_update(champion);
            video_clear_back_buffer(0);
            champion_draw(champion);
            video_swap_buffers();
          }
        }
        break;
      default:
        break;
      }
    }

    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    destroy_champion(champion);

    vg_exit();

    return 0;
}
