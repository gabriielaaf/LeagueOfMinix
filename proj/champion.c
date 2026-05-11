#include "champion.h"
#include <stdlib.h>


struct Champion
{
    int x;
    int y;

    int hp;
    int speed;
    int attack_dmg;
    int ability_dmg;

    int currentAnimation;
    AnimSprite **animations;
    int numAnimations;
};

Champion *create_champion(int x, int y, int hp, int speed, int attack_dmg, int ability_dmg,AnimSprite **animations,int numAnimations) {
    
   if (animations == NULL || numAnimations <= 0) {
        return NULL;
    }

    Champion *champion = malloc(sizeof(Champion));
    
    if (champion == NULL) {
        return NULL;
    }

    champion->x = x;
    champion->y = y;
    champion->hp = hp;
    champion->attack_dmg = attack_dmg;
    champion->ability_dmg = ability_dmg;
    champion->speed = speed;

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
    champion->x += dx;
    champion->y += dy;
}

void champion_set_animation(Champion *champion, int animation){

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

