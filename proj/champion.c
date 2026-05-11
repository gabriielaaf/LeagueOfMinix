#include "champion.h"

struct Champion
{
    int x;
    int y;

    int hp;
    int speed;
    int attack_dmg;
    int ability_dmg;
};

Champion *create_champion(int x, int y, int hp, int speed, int attack_dmg, int ability_dmg) {
    Champion *champion = malloc(sizeof(Champion));
    
    if (champion == NULL) {
      return NULL;
    }

    champion->x = x;
    champion->y = y;
    champion->hp = hp;
    champion->attack_dmg = attack_dmg;
    champion->ability_dmg = ability_dmg;
    return champion;
}

void moveChampion(struct Champion *champion, int dx, int dy) {
    champion->x += dx;
    champion->y += dy;
}

