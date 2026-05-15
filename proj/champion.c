#include "champion.h"
#include <stdlib.h>

#define HP 100
#define SPEED 1
#define ATTACK_DMG 10
#define ABILITY_DMG 30


struct Champion
{
    int x;
    int y;

    int hp;
    int speed;
    int attack_dmg;
    int ability_dmg;

    Direction dir;

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
    champion->ability_dmg = ABILITY_DMG;
    champion->speed = SPEED;

    champion->dir = SOUTH;

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

    champion->currentAnimation = (int)champion->dir;
}

void attack_champion(struct Champion *champion_attacking, struct Champion *champion_attacked) {
    champion_attacked->hp -= champion_attacking->attack_dmg; 
}

void ability_damaged_champion(struct Champion *champion_attacking, struct Champion *champion_attacked){
    champion_attacked->hp -= champion_attacking->ability_dmg;
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

    update_AnimSprite(champion->animations[champion->currentAnimation]);
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

