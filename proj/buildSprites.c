#include <stdlib.h>
#include "buildSprites.h"

static xpm_row_t *p1_idle_xpms[8] = {
    p1_north_stop_xpm,
    p1_south_stop_xpm,
    p1_east_stop_xpm,
    p1_west_stop_xpm,
    p1_north_east_stop_xpm,
    p1_north_west_stop_xpm,
    p1_south_east_stop_xpm,
    p1_south_west_stop_xpm,
};

static xpm_row_t *p1_move_xpms[8][MOVE_FRAMES] = {
    {p1_north_move1_xpm,     p1_north_move2_xpm},
    {p1_south_move1_xpm,     p1_south_move2_xpm},
    {p1_east_move1_xpm,      p1_east_move2_xpm},
    {p1_west_move1_xpm,      p1_west_move2_xpm},
    {p1_north_east_move1_xpm, p1_north_east_move2_xpm},
    {p1_north_west_move1_xpm, p1_north_west_move2_xpm},
    {p1_south_east_move1_xpm, p1_south_east_move2_xpm},
    {p1_south_west_move1_xpm, p1_south_west_move2_xpm},
};

static xpm_row_t *p1_attack_xpms[8][ATTACK_FRAMES] = {
    {p1_north_attack_up_xpm,
      p1_north_attack_mid_xpm,
      p1_north_attack_down_xpm},

    {p1_south_attack_up_xpm,
      p1_south_attack_mid_xpm,
      p1_south_attack_down_xpm},

    {p1_east_attack_up_xpm,
      p1_east_attack_mid_xpm,
      p1_east_attack_down_xpm},

    {p1_west_attack_up_xpm,
      p1_west_attack_mid_xpm,
      p1_west_attack_down_xpm},

    {p1_north_east_attack_up_xpm,
      p1_north_east_attack_mid_xpm,
      p1_north_east_attack_down_xpm},

    {p1_north_west_attack_up_xpm,
      p1_north_west_attack_mid_xpm,
      p1_north_west_attack_down_xpm},

    {p1_south_east_attack_up_xpm,
      p1_south_east_attack_mid_xpm,
      p1_south_east_attack_down_xpm},

    {p1_south_west_attack_up_xpm,
      p1_south_west_attack_mid_xpm,
      p1_south_west_attack_down_xpm},
};

static xpm_row_t *p2_idle_xpms[8] = {
    p2_north_stop_xpm,
    p2_south_stop_xpm,
    p2_east_stop_xpm,
    p2_west_stop_xpm,
    p2_north_east_stop_xpm,
    p2_north_west_stop_xpm,
    p2_south_east_stop_xpm,
    p2_south_west_stop_xpm,
};

static xpm_row_t *p2_move_xpms[8][MOVE_FRAMES] = {
    {p2_north_stop_xpm, p2_north_stop_xpm},
    {p2_south_move1_xpm, p2_south_move2_xpm},
    {p2_east_stop_xpm, p2_east_stop_xpm},
    {p2_west_move1_xpm, p2_west_move2_xpm},
    {p2_north_east_stop_xpm, p2_north_east_stop_xpm},
    {p2_north_west_stop_xpm, p2_north_west_stop_xpm},
    {p2_south_east_stop_xpm, p2_south_east_stop_xpm},
    {p2_south_west_move1_xpm, p2_south_west_move2_xpm},
};

static xpm_row_t *p2_attack_xpms[8][ATTACK_FRAMES] = {
    {p2_north_attack_up_xpm,
      p2_north_attack_mid_xpm,
      p2_north_attack_down_xpm},

    {p2_south_attack_up_xpm,
      p2_south_attack_mid_xpm,
      p2_south_attack_down_xpm},

    {p2_east_attack_up_xpm,
      p2_east_attack_mid_xpm,
      p2_east_down_xpm},

    {p2_west_attack_up_xpm,
      p2_west_attack_mid_xpm,
      p2_west_attack_down_xpm},

    {p2_north_east_attack_up_xpm,
      p2_north_east_attack_mid_xpm,
      p2_north_east_attack_down_xpm},

    {p2_north_west_attack_up_xpm,
      p2_north_west_attack_mid_xpm,
      p2_north_west_attack_down_xpm},

    {p2_south_east_attack_up_xpm,
      p2_south_east_attack_mid_xpm,
      p2_south_east_attack_down_xpm},

    {p2_south_west_attack_up_xpm,
      p2_south_west_attack_mid_xpm,
      p2_south_west_attack_down_xpm},
};

static void destroy_animations(AnimSprite **animations, int count) {
    for (int i = 0; i < count; i++)
        destroyAnimSprite(animations[i]);
    free(animations);
}

AnimSprite **build_animations(int player) {
    AnimSprite **animations = malloc(NUM_ANIMS * sizeof(AnimSprite *));
    if (animations == NULL)
        return NULL;

    int anims_created = 0;

    for (int i = 0; i < 8; i++) {
        Sprite *s = NULL;
        switch (player) {
            case 1:
                s = sprite_create(p1_idle_xpms[i]);
                break;
            case 2:
                s = sprite_create(p2_idle_xpms[i]);
                break;
            default:
                break;
        }

        if (s == NULL) {
            destroy_animations(animations, anims_created);
            return NULL;
        }

        Sprite **frames = malloc(sizeof(Sprite *));
        if (frames == NULL) {
            sprite_destroy(s);
            destroy_animations(animations, anims_created);
            return NULL;
        }

        frames[0] = s;
        animations[i] = createAnimSprite(1, 1, 350, 220, frames);

        if (animations[i] == NULL) {
            free(frames);
            sprite_destroy(s);
            destroy_animations(animations, anims_created);
            return NULL;
        }
        anims_created++;
    }

    for (int i = 0; i < 8; i++) {
        Sprite **frames = malloc(ATTACK_FRAMES * sizeof(Sprite *));
        if (frames == NULL) {
            destroy_animations(animations, anims_created);
            return NULL;
        }

        int frames_ok = 0;
        for (int f = 0; f < ATTACK_FRAMES; f++) {
            switch (player) {
                case 1:
                    frames[f] = sprite_create(p1_attack_xpms[i][f]);
                    break;
                case 2:
                    frames[f] = sprite_create(p2_attack_xpms[i][f]);
                    break;
                default:
                    break;
            }
            
            if (frames[f] == NULL) {
                for (int k = 0; k < frames_ok; k++)
                    sprite_destroy(frames[k]);
                free(frames);
                destroy_animations(animations, anims_created);
                return NULL;
            }
            frames_ok++;
        }
        
        animations[8 + i] = createAnimSprite(ATTACK_TIME, ATTACK_FRAMES, 350, 220, frames);
        if (animations[8 + i] == NULL) {
            for (int f = 0; f < ATTACK_FRAMES; f++)
                sprite_destroy(frames[f]);
            free(frames);
            destroy_animations(animations, anims_created);
            return NULL;
        }
        anims_created++;
    }

    for (int i = 0; i < 8; i++) {
        Sprite **frames = malloc(MOVE_FRAMES * sizeof(Sprite *));
        if (frames == NULL) {
            destroy_animations(animations, anims_created);
            return NULL;
        }

        int frames_ok = 0;
        for (int f = 0; f < MOVE_FRAMES; f++) {
            frames[f] = sprite_create(player == 1 ? p1_move_xpms[i][f] : p2_move_xpms[i][f]);
            if (frames[f] == NULL) {
                for (int k = 0; k < frames_ok; k++) sprite_destroy(frames[k]);
                free(frames);
                destroy_animations(animations, anims_created);
                return NULL;
            }
            frames_ok++;
        }

        animations[16 + i] = createAnimSprite(MOVE_TIME, MOVE_FRAMES, 350, 220, frames);
        if (animations[16 + i] == NULL) {
            for (int f = 0; f < MOVE_FRAMES; f++) sprite_destroy(frames[f]);
            free(frames);
            destroy_animations(animations, anims_created);
            return NULL;
        }
        anims_created++;
    }

    return animations;
}
