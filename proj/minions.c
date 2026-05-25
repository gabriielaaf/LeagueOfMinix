#include "minions.h"
#include "video.h"
#include <stdlib.h>
#include <stdint.h>

#define MINION_HP 100
#define MINION_SPEED 2
#define MINION_ATTACK_DMG 10
#define MINION_ATTACK_SPEED 20   /* ticks between attacks (~1s at 20 UPS) */
#define ATTACK_RANGE 55   /* center-to-center px */

#define RED_COLOR 4
#define BLUE_COLOR 9

static bool boxes_overlap(Box a, Box b) {
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}

static bool in_attack_range(Minion *a, Minion *b) {
    int dx = (a->x + MINION_W / 2) - (b->x + MINION_W / 2);
    int dy = (a->y + MINION_H / 2) - (b->y + MINION_H / 2);
    return (dx * dx + dy * dy) <= (ATTACK_RANGE * ATTACK_RANGE);
}

static void init_wave(MinionWave *wave, MinionTeam team) {
    wave->active = true;
    for (int i = 0; i < MINION_COUNT; i++) {
        wave->minions[i].team = team;
        wave->minions[i].hp = MINION_HP;
        wave->minions[i].state = MINION_MOVING;
        wave->minions[i].attack_timer = 0;
        wave->minions[i].y = MINION_LANE_Y + i * (MINION_H + MINION_SPACING);
        wave->minions[i].x = (team == MINION_RED) ? 0 : MODE105_WIDTH - MINION_W;
    }
}

static void spawn_wave_pair(MinionsManager *mgr) {
    int ri = -1, bi = -1;
    for (int i = 0; i < MAX_WAVES; i++) {
        if (!mgr->red_waves[i].active && ri < 0) ri = i;
        if (!mgr->blue_waves[i].active && bi < 0) bi = i;
    }
    if (ri < 0 || bi < 0) return;

    init_wave(&mgr->red_waves[ri], MINION_RED);
    mgr->red_count++;
    init_wave(&mgr->blue_waves[bi], MINION_BLUE);
    mgr->blue_count++;
}

void minions_manager_init(MinionsManager *mgr) {
    for (int i = 0; i < MAX_WAVES; i++) {
        mgr->red_waves[i].active = false;
        mgr->blue_waves[i].active = false;
    }
    mgr->red_count = 0;
    mgr->blue_count = 0;
    mgr->spawn_timer = 0;
    spawn_wave_pair(mgr);
}

static bool wave_all_dead(MinionWave *wave) {
    for (int i = 0; i < MINION_COUNT; i++)
        if (wave->minions[i].state != MINION_DEAD) return false;
    return true;
}

/* Find nearest living enemy minion across all enemy waves */
static Minion *find_nearest_enemy(Minion *m, MinionsManager *mgr) {
    MinionWave *enemy_waves = (m->team == MINION_RED) ? mgr->blue_waves : mgr->red_waves;
    Minion *nearest = NULL;
    int min_dist = INT32_MAX;

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!enemy_waves[w].active) continue;
        for (int j = 0; j < MINION_COUNT; j++) {
            Minion *e = &enemy_waves[w].minions[j];
            if (e->state == MINION_DEAD) continue;
            int dx = (m->x + MINION_W / 2) - (e->x + MINION_W / 2);
            int dy = (m->y + MINION_H / 2) - (e->y + MINION_H / 2);
            int dist = dx * dx + dy * dy;
            if (dist < min_dist) { min_dist = dist; nearest = e; }
        }
    }
    return nearest;
}

static void update_minion(Minion *m, MinionsManager *mgr, int dir) {
    if (m->state == MINION_DEAD) return;
    if (m->hp <= 0) { m->state = MINION_DEAD; return; }

    Minion *target = find_nearest_enemy(m, mgr);

    if (target != NULL && in_attack_range(m, target)) {
        m->state = MINION_ATTACKING;
        m->attack_timer++;
        if (m->attack_timer >= MINION_ATTACK_SPEED) {
            target->hp -= MINION_ATTACK_DMG;
            m->attack_timer = 0;
        }
        return;
    }

    m->state = MINION_MOVING;
    m->attack_timer = 0;
    m->x += dir * MINION_SPEED;
}

void update_minions_manager(MinionsManager *mgr) {
    mgr->spawn_timer++;
    if (mgr->spawn_timer >= SPAWN_INTERVAL) {
        mgr->spawn_timer = 0;
        spawn_wave_pair(mgr);
    }

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!mgr->red_waves[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++)
            update_minion(&mgr->red_waves[w].minions[i], mgr, +1);
        if (wave_all_dead(&mgr->red_waves[w])) {
            mgr->red_waves[w].active = false;
            mgr->red_count--;
        }
    }

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!mgr->blue_waves[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++)
            update_minion(&mgr->blue_waves[w].minions[i], mgr, -1);
        if (wave_all_dead(&mgr->blue_waves[w])) {
            mgr->blue_waves[w].active = false;
            mgr->blue_count--;
        }
    }
}

int draw_minions_manager(MinionsManager *mgr) {
    for (int w = 0; w < MAX_WAVES; w++) {
        if (mgr->red_waves[w].active) {
            for (int i = 0; i < MINION_COUNT; i++) {
                Minion *m = &mgr->red_waves[w].minions[i];
                if (m->state == MINION_DEAD) continue;
                if (vg_draw_rectangle((uint16_t)m->x, (uint16_t)m->y,
                                      MINION_W, MINION_H, RED_COLOR) != 0)
                    return 1;
            }
        }
        if (mgr->blue_waves[w].active) {
            for (int i = 0; i < MINION_COUNT; i++) {
                Minion *m = &mgr->blue_waves[w].minions[i];
                if (m->state == MINION_DEAD) continue;
                if (vg_draw_rectangle((uint16_t)m->x, (uint16_t)m->y,
                                      MINION_W, MINION_H, BLUE_COLOR) != 0)
                    return 1;
            }
        }
    }
    return 0;
}

void minions_manager_take_hit(MinionsManager *mgr, Box attack_box, int damage) {
    for (int w = 0; w < MAX_WAVES; w++) {
        if (mgr->red_waves[w].active) {
            for (int i = 0; i < MINION_COUNT; i++) {
                Minion *m = &mgr->red_waves[w].minions[i];
                if (m->state == MINION_DEAD) continue;
                Box mb = {m->x, m->y, MINION_W, MINION_H};
                if (boxes_overlap(attack_box, mb)) m->hp -= damage;
            }
        }
        if (mgr->blue_waves[w].active) {
            for (int i = 0; i < MINION_COUNT; i++) {
                Minion *m = &mgr->blue_waves[w].minions[i];
                if (m->state == MINION_DEAD) continue;
                Box mb = {m->x, m->y, MINION_W, MINION_H};
                if (boxes_overlap(attack_box, mb)) m->hp -= damage;
            }
        }
    }
}
