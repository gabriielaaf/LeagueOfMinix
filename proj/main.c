#include <lcom/lcf.h>
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
     * Normal main: Yasuo attack animation with WASD movement.
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

    Sprite *attack_frames[] = {attack_up, attack_mid, attack_down};

    AnimSprite *attack_anim = createAnimSprite(5, 3, 350, 220, attack_frames);

    if (attack_anim == NULL) {
        sprite_destroy(attack_up);
        sprite_destroy(attack_mid);
        sprite_destroy(attack_down);

        vg_exit();
        return 1;
    }

    AnimSprite *animations[] = {attack_anim};

    Champion *champion = create_champion(350, 220, animations, 1);

    if (champion == NULL) {
        destroyAnimSprite(attack_anim);

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
                        keyboard_interpret_scancode(&kstate, get_scancode_bytes(), get_scancode_size());
                        reset_scancode();
                    }
                }

                if (msg.m_notify.interrupts & timer_irq_set) {
                    timer_int_handler();

                    int dx = 0, dy = 0;
                    if (kstate.p1.left)  dx -= 1;
                    if (kstate.p1.right) dx += 1;
                    if (kstate.p1.up)    dy -= 1;
                    if (kstate.p1.down)  dy += 1;
                    moveChampion(champion, dx, dy);

                    champion_update(champion);
                    video_clear_back_buffer(0);
                    champion_draw(champion);
                    video_swap_buffers();
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
