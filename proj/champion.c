#include "champion.h"
#include <stdlib.h>

#define HP 100
#define SPEED 1
#define ATTACK_DMG 10
#define ATTACK_SPEED 5

struct Champion {
    int x;
    int y;

    int hp;
    int speed;
    int attack_dmg;
    int attack_speed;

    Direction dir;
    ChampionState state;

    int currentAnimation;
    AnimSprite **animations;
    int numAnimations;
};

Champion *create_champion(int x, int y, AnimSprite **animations,int numAnimations) {
    if (animations == NULL || numAnimations <= 0) {
        return NULL;
    }

    Champion *champion = malloc(sizeof(Champion));
    
    if (champion == NULL) {
        return NULL;
    }

    champion->x = x;
    champion->y = y;
    champion->hp = HP;
    champion->attack_dmg = ATTACK_DMG;
    champion->speed = SPEED;
    champion->attack_speed = ATTACK_SPEED;

    champion->dir = SOUTH;
    champion->state = CHAMPION_IDLE;

    champion->currentAnimation = 0;
    champion->animations = animations;
    champion->numAnimations = numAnimations;

    return champion;
}

void destroy_champion(Champion *champion) {
    if (champion == NULL) {
        return;
    }

    if (champion->animations != NULL) {
        for (int i = 0; i < champion->numAnimations; i++) {
            destroyAnimSprite(champion->animations[i]);
        }
    }

    free(champion);
}

void moveChampion(struct Champion *champion, int dx, int dy) {
    champion->x += dx * SPEED;
    champion->y += dy * SPEED;

    if (dx == 0 && dy == 0) return;

    if      (dx == 0 && dy < 0) champion->dir = NORTH;
    else if (dx == 0 && dy > 0) champion->dir = SOUTH;
    else if (dx > 0 && dy == 0) champion->dir = EAST;
    else if (dx < 0 && dy == 0) champion->dir = WEST;
    else if (dx > 0 && dy < 0) champion->dir = NORTHEAST;
    else if (dx < 0 && dy < 0) champion->dir = NORTHWEST;
    else if (dx > 0 && dy > 0) champion->dir = SOUTHEAST;
    else                        champion->dir = SOUTHWEST;

    if (champion->state == CHAMPION_IDLE) {
        champion->currentAnimation = (int)champion->dir;
    }
}

void champion_attack(Champion *champion) {
    if (champion == NULL || champion->state == CHAMPION_ATTACKING)
        return;

    champion->state = CHAMPION_ATTACKING;
    int attack_anim = (int)champion->dir + 8;
    champion->currentAnimation = attack_anim;
    
    animSprite_reset(champion->animations[attack_anim]);
}

void attack_damaged_champion(struct Champion *champion_attacking, struct Champion *champion_attacked) {
    champion_attacked->hp -= champion_attacking->attack_dmg; 
}

void champion_set_animation(Champion *champion, int animation) {
    if (champion == NULL) {
        return;
    }

    if (animation < 0 || animation >= champion->numAnimations) {
        return;
    }

    champion->currentAnimation = animation;
}

void champion_update(Champion *champion) {
    if (champion == NULL || champion->animations == NULL) {
        return;
    }

    AnimSprite *anim = champion->animations[champion->currentAnimation];
    update_AnimSprite(anim);

    if (champion->state == CHAMPION_ATTACKING && animSprite_has_looped(anim)) {
        champion->state = CHAMPION_IDLE;
        champion->currentAnimation = (int)champion->dir;
    }
    if (champion->state == CHAMPION_MOVING && animSprite_has_looped(anim)) {
      champion->state = CHAMPION_IDLE;
      champion->currentAnimation = (int)champion->dir;
    }
}

int champion_draw(Champion *champion) {
    if (champion == NULL || champion->animations == NULL) {
        return 1;
    }

    setAnimSpritePosition(
        champion->animations[champion->currentAnimation],
        champion->x,
        champion->y
    );

    return drawAnimSprite(champion->animations[champion->currentAnimation]);
}
