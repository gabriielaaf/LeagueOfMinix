#include "TowerController.h"
#include "ChampionController.h"
#include "../model/minion/MinionConfig.h"
#include "../model/tower/TowerConfig.h"
#include <math.h>

static bool minionInRange(Tower *t, Minion *m) {
    int tcx = position_px(t->pos) + TOWER_W / 2;
    int tcy = position_py(t->pos) + TOWER_H / 2;
    int dx = tcx - (position_px(m->pos) + MINION_W / 2);
    int dy = tcy - (position_py(m->pos) + MINION_H / 2);
    return (dx * dx + dy * dy) <= TOWER_RANGE * TOWER_RANGE;
}

static bool championInRange(Tower *t, Champion *champ) {
    if (!champ || championGetHp(champ) <= 0) return false;
    int tcx = position_px(t->pos) + TOWER_W / 2;
    int tcy = position_py(t->pos) + TOWER_H / 2;
    Position p = championGetPos(champ);
    int dx = tcx - (position_px(p) + championGetWidth(champ) / 2);
    int dy = tcy - (position_py(p) + championGetHeight(champ) / 2);
    return (dx * dx + dy * dy) <= TOWER_RANGE * TOWER_RANGE;
}

static Minion *findNearestMinion(Tower *t, Minions *minions) {
    int tcx = position_px(t->pos) + TOWER_W / 2;
    int tcy = position_py(t->pos) + TOWER_H / 2;
    MinionWave *enemy = (t->team == TEAM_BLUE) ? minions->red_waves : minions->blue_waves;
    Minion *best = NULL;
    int min_dist = TOWER_RANGE * TOWER_RANGE;

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!enemy[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++) {
            Minion *m = &enemy[w].minions[i];
            if (m->state == MINION_DEAD) continue;
            int dx = tcx - (position_px(m->pos) + MINION_W / 2);
            int dy = tcy - (position_py(m->pos) + MINION_H / 2);
            int dist = dx * dx + dy * dy;
            if (dist < min_dist) { min_dist = dist; best = m; }
        }
    }
    return best;
}

static void updateProjectile(TowerProjectile *p, Champion *enemy_champ) {
    if (!p->active) return;

    float tx, ty;
    if (p->minion_target != NULL) {
        if (p->minion_target->state == MINION_DEAD) { p->active = false; return; }
        tx = p->minion_target->pos.x + MINION_W / 2.0f;
        ty = p->minion_target->pos.y + MINION_H / 2.0f;
    } else {
        if (!enemy_champ || championGetHp(enemy_champ) <= 0) { p->active = false; return; }
        Position cp = championGetPos(enemy_champ);
        tx = cp.x + championGetWidth(enemy_champ) / 2.0f;
        ty = cp.y + championGetHeight(enemy_champ) / 2.0f;
    }

    float dx = tx - p->pos.x;
    float dy = ty - p->pos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist <= PROJECTILE_HIT_RADIUS) {
        if (p->minion_target != NULL) {
            p->minion_target->hp -= p->damage;
        } else {
            championDecreaseHp(enemy_champ, p->damage);
        }
        p->active = false;
    } else {
        p->pos.x += (dx / dist) * PROJECTILE_SPEED;
        p->pos.y += (dy / dist) * PROJECTILE_SPEED;
    }
}

static void updateTower(Tower *t, Minions *minions, Champion *enemy_champ) {
    if (t->hp <= 0) return;

    updateProjectile(&t->projectile, enemy_champ);

    t->attack_timer++;
    if (t->attack_timer < TOWER_ATTACK_SPEED) return;
    t->attack_timer = 0;

    // Validate locked minion: dead or walked out of range
    if (t->minion_target != NULL) {
        if (t->minion_target->state == MINION_DEAD || !minionInRange(t, t->minion_target)) {
            t->minion_target = NULL;
            t->targeting_champion = false;
        }
    }

    // Validate champion lock: died or left range
    if (t->targeting_champion && !championInRange(t, enemy_champ))
        t->targeting_champion = false;

    // Acquire a new target only if we have none (minions have priority)
    if (t->minion_target == NULL && !t->targeting_champion) {
        t->minion_target = findNearestMinion(t, minions);
        if (t->minion_target == NULL)
            t->targeting_champion = championInRange(t, enemy_champ);
    }

    if (t->minion_target == NULL && !t->targeting_champion) return;

    t->projectile.pos.x = position_px(t->pos) + TOWER_W / 2.0f;
    t->projectile.pos.y = position_py(t->pos) + TOWER_H / 2.0f;
    t->projectile.minion_target    = t->minion_target;
    t->projectile.targeting_champion = t->targeting_champion;
    t->projectile.damage = TOWER_DMG;
    t->projectile.active = true;
}

void towersUpdate(Towers *towers, Minions *minions, Champion *p1, Champion *p2) {
    updateTower(&towers->blue, minions, p2);
    updateTower(&towers->red,  minions, p1);
}
