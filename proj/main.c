#include <lcom/lcf.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "video.h"
#include "keyboard.h"
#include "vbe.h"

#include "viewer/sprite/Sprite.h"

#include "assets/arena.h"
#include "assets/tower_p1_xpm.h"
#include "assets/p1/p1_south_xpms.h"

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
    (void) argc;
    (void) argv;

    lazy_link();

    if (video_init_page_flipping(0x118) != 0) {
        return 1;
    }

    Sprite *background = spriteCreate(background_xpm);
    if (background == NULL) {
        vg_exit();
        return 1;
    }

    Sprite *tower = spriteCreate(blue_tower_xpm);
    if (tower == NULL) {
        spriteDestroy(background);
        vg_exit();
        return 1;
    }

    Sprite *player = spriteCreate(p1_south_stop_xpm);
    if (player == NULL) {
        spriteDestroy(tower);
        spriteDestroy(background);
        vg_exit();
        return 1;
    }

    uint8_t timer_bit_no;
    if (timer_subscribe_int(&timer_bit_no) != 0) {
        spriteDestroy(player);
        spriteDestroy(tower);
        spriteDestroy(background);
        vg_exit();
        return 1;
    }

    uint8_t kbd_bit_no;
    if (kbd_subscribe_int(&kbd_bit_no) != 0) {
        timer_unsubscribe_int();
        spriteDestroy(player);
        spriteDestroy(tower);
        spriteDestroy(background);
        vg_exit();
        return 1;
    }

    uint32_t timer_irq_set = BIT(timer_bit_no);
    uint32_t kbd_irq_set = BIT(kbd_bit_no);

    int player_x = 462;
    int player_y = 560;

    bool move_up = false;
    bool move_down = false;
    bool move_left = false;
    bool move_right = false;
    bool running = true;

    int ipc_status;
    message msg;
    int r;

    while (running) {
        r = driver_receive(ANY, &msg, &ipc_status);

        if (r != 0) {
            continue;
        }

        if (!is_ipc_notify(ipc_status)) {
            continue;
        }

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
                        uint8_t *bytes = get_scancode_bytes();
                        uint8_t size = get_scancode_size();

                        if (size == 1) {
                            switch (bytes[0]) {
                                case 0x11: // W make
                                    move_up = true;
                                    break;

                                case 0x91: // W break
                                    move_up = false;
                                    break;

                                case 0x1F: // S make
                                    move_down = true;
                                    break;

                                case 0x9F: // S break
                                    move_down = false;
                                    break;

                                case 0x1E: // A make
                                    move_left = true;
                                    break;

                                case 0x9E: // A break
                                    move_left = false;
                                    break;

                                case 0x20: // D make
                                    move_right = true;
                                    break;

                                case 0xA0: // D break
                                    move_right = false;
                                    break;

                                case 0x81: // ESC break
                                    running = false;
                                    break;

                                default:
                                    break;
                            }
                        }

                        reset_scancode();
                    }
                }

                if (msg.m_notify.interrupts & timer_irq_set) {
                    int speed = 4;

                    if (move_up) player_y -= speed;
                    if (move_down) player_y += speed;
                    if (move_left) player_x -= speed;
                    if (move_right) player_x += speed;

                    if (player_x < 0) player_x = 0;
                    if (player_y < 0) player_y = 0;
                    if (player_x > 1024 - 100) player_x = 1024 - 100;
                    if (player_y > 768 - 100) player_y = 768 - 100;

                    video_clear_back_buffer(spriteGetMap(background));


                    spriteDraw(tower, 430, 250);
                    spriteDraw(player, player_x, player_y);

                    video_swap_buffers();
                }

                break;

            default:
                break;
        }
    }

    kbd_unsubscribe_int();
    timer_unsubscribe_int();

    spriteDestroy(player);
    spriteDestroy(tower);
    spriteDestroy(background);

    vg_exit();

    return 0;
}
