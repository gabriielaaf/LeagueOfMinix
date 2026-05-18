#include <stdlib.h>
#include "buildSprites.h"

static xpm_row_t *idle_xpms[8] = {
    yasuo_north_stop_xpm,
    yasuo_south_stop_xpm,
    yasuo_east_stop_xpm,
    yasuo_west_stop_xpm,
    yasuo_north_east_stop_xpm,
    yasuo_north_west_stop_xpm,
    yasuo_south_east_stop_xpm,
    yasuo_south_west_stop_xpm,
};

static xpm_row_t *attack_xpms[8][ATTACK_FRAMES] = {
    {yasuo_north_attack_up_xpm,      
      yasuo_north_attack_mid_xpm,      
      yasuo_north_attack_down_xpm},

    {yasuo_south_attack_up_xpm,      
      yasuo_south_attack_mid_xpm,      
      yasuo_south_attack_down_xpm},

    {yasuo_east_attack_up_xpm,       
      yasuo_east_attack_mid_xpm,       
      yasuo_east_down_xpm},

    {yasuo_west_attack_up_xpm,       
      yasuo_west_attack_mid_xpm,       
      yasuo_west_attack_down_xpm},

    {yasuo_north_east_attack_up_xpm, 
      yasuo_north_east_attack_mid_xpm, 
      yasuo_north_east_attack_down_xpm},

    {yasuo_north_west_attack_up_xpm, 
      yasuo_north_west_attack_mid_xpm, 
      yasuo_north_west_attack_down_xpm},

    {yasuo_south_east_attack_up_xpm, 
      yasuo_south_east_attack_mid_xpm, 
      yasuo_south_east_attack_down_xpm},

    {yasuo_south_west_attack_up_xpm, 
      yasuo_south_west_attack_mid_xpm, 
      yasuo_south_west_attack_down_xpm},
};

static void destroy_animations(AnimSprite **animations, int count) {
    for (int i = 0; i < count; i++)
        destroyAnimSprite(animations[i]);
    free(animations);
}

AnimSprite **build_animations() {
    AnimSprite **animations = malloc(NUM_ANIMS * sizeof(AnimSprite *));
    if (animations == NULL)
        return NULL;

    int anims_created = 0;

    for (int i = 0; i < 8; i++) {
        Sprite *s = sprite_create(idle_xpms[i]);
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
            frames[f] = sprite_create(attack_xpms[i][f]);
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

    return animations;
}
