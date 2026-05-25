#include <lcom/lcf.h>
#include <lcom/proj.h>

#include <stdlib.h>
#include <string.h>

#include "video.h"
#include "keyboard.h"
#include "mouse.h"
#include "keyboardInterpreter.h"
#include "mouseInterpreter.h"

#include "sprite.h"
#include "animSprite.h"
#include "champion.h"
#include "buildSprites.h"
#include "minions.h"

#include "assets/gabiteste.h"

void lazy_link();

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

    AnimSprite **animations1 = build_animations(1);
    AnimSprite **animations2 = build_animations(2);
    if (animations1 == NULL || animations2 == NULL) {
        vg_exit();
        return 1;
    }

    MinionsManager mgr;
    minions_manager_init(&mgr);

    Champion *champion_p1 = create_champion(350, 220, animations1, NUM_ANIMS);
    Champion *champion_p2 = create_champion(500, 500, animations2, NUM_ANIMS);
    if (champion_p1 == NULL) {
      for (int i = 0; i < NUM_ANIMS; i++)
        destroyAnimSprite(animations1[i]);
      free(animations1);
      vg_exit();
      return 1;
    }

    if (champion_p2 == NULL) {
      for (int i = 0; i < NUM_ANIMS; i++)
        destroyAnimSprite(animations2[i]);
      free(animations2);
      vg_exit();
      return 1;
    }

    lazy_link(); // NÃO REMOVER, NECESSÁRIO POR CAUSA DO LAZY LINK E DO CONFLITO COM A LCF

    uint8_t timer_bit_no;
    if (timer_subscribe_int(&timer_bit_no) != 0) {
        destroy_champion(champion_p1);
        vg_exit();
        return 1;
    }
    timer_set_frequency(0, 60);

    uint8_t kbd_bit_no;
    if (kbd_subscribe_int(&kbd_bit_no) != 0) {
        timer_unsubscribe_int();
        destroy_champion(champion_p1);
        vg_exit();
        return 1;
    }

    uint8_t mouse_bit_no;
    if (mouse_subscribe_int(&mouse_bit_no) != 0) {
        mouse_unsubscribe_int();
        destroy_champion(champion_p1);
        vg_exit();
        return 1;
    }

    uint32_t timer_irq_set = BIT(timer_bit_no);
    uint32_t kbd_irq_set = BIT(kbd_bit_no);
    uint32_t mouse_irq_set = BIT(mouse_bit_no);

    KeyboardState kstate;
    keyboard_state_init(&kstate);

    MouseState mstate;
    mouse_state_init(&mstate, 0, 0);

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

            if (msg.m_notify.interrupts & mouse_irq_set) {
                mouse_ih();
                if (packet_complete()) {
                    mouse_interpret_packet(&mstate, get_packet());
                    reset_packet();
                }
            }

            if (msg.m_notify.interrupts & timer_irq_set) {
            timer_int_handler();
            counter++;
                if (counter == 3) {
                    counter = 0;
                    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
                    if (kstate.p1.left)
                    dx1 -= 1;
                    if (kstate.p1.right)
                    dx1 += 1;
                    if (kstate.p1.up)
                    dy1 -= 1;
                    if (kstate.p1.down)
                    dy1 += 1;
                    if (kstate.p2.left)
                    dx2 -= 1;
                    if (kstate.p2.right)
                    dx2 += 1;
                    if (kstate.p2.up)
                    dy2 -= 1;
                    if (kstate.p2.down)
                    dy2 += 1;

                    moveChampion(champion_p1, champion_p2, dx1, dy1);
                    moveChampion(champion_p2, champion_p1, dx2, dy2);

                    if (mstate.p1.attack) {
                        champion_attack(champion_p1);
                        if (champion_attack_hits(champion_p1, champion_p2)) {
                          decrease_target_hp(champion_p1, champion_p2);
                        }
                        minions_manager_take_hit(&mgr, champion_get_attack_box(champion_p1), 10);
                    }

                    if (mstate.p2.attack) {
                        champion_attack(champion_p2);
                        if (champion_attack_hits(champion_p2, champion_p1)) {
                          decrease_target_hp(champion_p2, champion_p1);
                        }
                        minions_manager_take_hit(&mgr, champion_get_attack_box(champion_p2), 10);
                    }

                    mouse_clear_events(&mstate);

                    update_minions_manager(&mgr);

                    champion_update(champion_p1);
                    champion_update(champion_p2);
                    video_clear_back_buffer(0);
                    draw_minions_manager(&mgr);
                    champion_draw(champion_p1);
                    champion_draw(champion_p2);
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
    mouse_unsubscribe_int();
    destroy_champion(champion_p1);
    destroy_champion(champion_p2);
    free(animations1);
    free(animations2);

    vg_exit();

    return 0;
}
