#include "champion.h"
#include <stdlib.h>

struct Champion {

    int respawn_x;
    int respawn_y;
    int x;
    int y;

    int hp;
    int speed;
    int attack_dmg;
    int attack_speed;

    int respawn_timer;

    Direction dir;
    ChampionState state;

    int currentAnimation;
    AnimSprite **animations;
    int numAnimations;
};

Champion *create_champion(int spawn_x, int spawn_y, AnimSprite **animations, int numAnimations, Direction dir) {
    if (animations == NULL || numAnimations <= 0) {
        return NULL;
    }

    Champion *champion = malloc(sizeof(Champion));
    
    if (champion == NULL) {
        return NULL;
    }

    champion->respawn_x = spawn_x;
    champion->respawn_y = spawn_y;
    if (spawn_x == RED_SPAWN_X) {
        champion->x = RED_SPAWN_X - getWidth(getCurrentSprite(animations[0]));
    }
    else {
        champion->x = spawn_x;
    }
    champion->y = spawn_y;
    champion->hp = HP;
    champion->attack_dmg = ATTACK_DMG;
    champion->speed = SPEED;
    champion->attack_speed = ATTACK_SPEED;

    champion->respawn_timer = ALIVE;

    champion->dir = dir;
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

Box champion_get_hit_box(Champion * champion){
  return (Box){champion->x, 
               champion->y,
               getWidth(getCurrentSprite(
                   champion->animations[champion->currentAnimation])),
               getHeight(getCurrentSprite(
                   champion->animations[champion->currentAnimation]))};
}

Box champion_get_collision_box(Champion *champion) {
    Sprite *sprite = getCurrentSprite(champion->animations[champion->currentAnimation]);
    int sprite_width = getWidth(sprite);
    int sprite_height = getHeight(sprite);
    int collision_width = (int)(sprite_width * COLLISION_PROPORTION);
    int collision_height = (int)(sprite_height * COLLISION_PROPORTION);
    Box box;
    box.x = champion->x + (sprite_width - collision_width) / 2;
    box.y = champion->y + (sprite_height - collision_height) / 2;
    box.w = collision_width;
    box.h = collision_height;
    return box;
}

Box champion_get_attack_box(Champion *champion) {
    Sprite *sprite = getCurrentSprite(champion->animations[champion->currentAnimation]);
    int sprite_width = getWidth(sprite);
    int sprite_height = getHeight(sprite);
    int x  = champion->x;
    int y  = champion->y;
    int offset_x = ATTACK_RANGE_OFFSET * sprite_width;
    int offset_y = ATTACK_RANGE_OFFSET * sprite_height;

    switch (champion->dir) {
        case NORTH: 
            return (Box){ x, y - offset_y, 
                sprite_width, 
                (sprite_height / 2) + offset_y};
        case SOUTH:
            return (Box){x, y + (sprite_height / 2), 
                sprite_width, 
                (sprite_height / 2) + offset_y};
        case EAST:
            return (Box){x + (sprite_width / 2), y, 
                (sprite_width / 2) + offset_x, 
                sprite_height};
        case WEST:
            return (Box){x - offset_x, y, 
                (sprite_width / 2) + offset_x, 
                sprite_height};
        case NORTHEAST:
            return (Box){x + (sprite_width / 2), y - offset_y, 
                (sprite_width / 2) + offset_x,
                (sprite_height / 2) + offset_y};
        case NORTHWEST:
            return (Box){x - offset_x, y - offset_y,
                (sprite_width / 2) + offset_x,
                (sprite_height / 2) + offset_y};
        case SOUTHEAST:
            return (Box){x + (sprite_width / 2), y + (sprite_height / 2),
                (sprite_width / 2) + offset_x,
                (sprite_height / 2) + offset_y};
        case SOUTHWEST:
            return (Box){x - offset_x, y + (sprite_height / 2),
                (sprite_width / 2) + offset_x,
                (sprite_height / 2) + offset_y};
        default:        
            return (Box){ x, y, sprite_width, sprite_height};
    }
}

static bool boxes_overlap(Box a, Box b) {
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}

static bool collide(struct Champion *c1, struct Champion *c2, int dx, int dy) {
    Box b1 = champion_get_collision_box(c1);
    b1.x += dx * SPEED;
    b1.y += dy * SPEED;
    Box b2 = champion_get_collision_box(c2);
    return boxes_overlap(b1, b2);
}

bool champion_attack_hits(Champion *attacker, Champion *target) {
    Box attacker_box = champion_get_attack_box(attacker);
    Box target_hit_box = champion_get_hit_box(target);
    return boxes_overlap(attacker_box, target_hit_box);
}

static bool canMove(struct Champion *champion, int dx, int dy) {
  int champion_width = getWidth(getCurrentSprite(champion->animations[champion->currentAnimation]));
  int champion_height = getHeight(
      getCurrentSprite(champion->animations[champion->currentAnimation]));
  int new_x = champion->x + dx * SPEED;
  int new_y = champion->y + dy * SPEED;

  if ((new_x) < 0 || (new_x + champion_width) > MODE105_WIDTH ||
      (new_y) < 0 || (new_y + champion_height) > MODE105_HEIGHT) {
    return false;
  }
    return true;
}

void moveChampion(struct Champion *champion1, struct Champion *champion2,int dx, int dy) {
    if (canMove(champion1, dx, dy) && !collide(champion1, champion2, dx, dy)) {
      champion1->x += dx * SPEED;
      champion1->y += dy * SPEED;
    }

    if (dx == 0 && dy == 0) return;

    if      (dx == 0 && dy < 0) champion1->dir = NORTH;
    else if (dx == 0 && dy > 0) champion1->dir = SOUTH;
    else if (dx > 0 && dy == 0) champion1->dir = EAST;
    else if (dx < 0 && dy == 0) champion1->dir = WEST;
    else if (dx > 0 && dy < 0) champion1->dir = NORTHEAST;
    else if (dx < 0 && dy < 0) champion1->dir = NORTHWEST;
    else if (dx > 0 && dy > 0) champion1->dir = SOUTHEAST;
    else                        champion1->dir = SOUTHWEST;

    if (champion1->state == CHAMPION_IDLE) {
        champion1->currentAnimation = (int)champion1->dir;
    }
}

bool champion_attack(Champion *champion) {
    if (champion == NULL || champion->state == CHAMPION_ATTACKING)
        return false;

    champion->state = CHAMPION_ATTACKING;
    int attack_anim = (int)champion->dir + 8;
    champion->currentAnimation = attack_anim;

    animSprite_reset(champion->animations[attack_anim]);
    return true;
}

void decrease_target_hp(struct Champion *attacker, struct Champion *target) {
    target->hp -= attacker->attack_dmg;
    if (target->hp <= 0) {
      target->respawn_timer = RESPAWN_INTERRUPTS;
    }
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

    if (champion->hp <= 0) {
        champion->respawn_timer--;
        if (champion->respawn_timer == 0) {
            champion->respawn_timer = ALIVE;
            champion->hp = HP;
            champion->x = champion->respawn_x;
            champion->y = champion->respawn_y;
        }
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
    if (champion == NULL || champion->animations == NULL || champion->hp <= 0) {
        return 1;
    }

    setAnimSpritePosition(
        champion->animations[champion->currentAnimation],
        champion->x,
        champion->y
    );

    return drawAnimSprite(champion->animations[champion->currentAnimation]);
}
