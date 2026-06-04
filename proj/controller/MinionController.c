#include "MinionController.h"

static void initWave(MinionWave *wave, Team team, int map_w) {
    wave->active = true;
    for (int i = 0; i < MINION_COUNT; i++) {
        wave->minions[i].team = team;
        wave->minions[i].hp = MINION_HP;
        wave->minions[i].state = MINION_MOVING;
        wave->minions[i].attack_timer = 0;
        wave->minions[i].pos.y = (float)(MINION_LANE_Y + i * (MINION_H + MINION_SPACING));
        wave->minions[i].pos.x = (float)((team == TEAM_BLUE) ? 0 : map_w - MINION_W);
    }
}

static void spawnWavePair(Minions *minions, int map_w) {
    int ri = -1, bi = -1;
    for (int i = 0; i < MAX_WAVES; i++) {
        if (!minions->red_waves[i].active && ri < 0) ri = i;
        if (!minions->blue_waves[i].active && bi < 0) bi = i;
    }
    if (ri < 0 || bi < 0) return;

    initWave(&minions->red_waves[ri], TEAM_RED, map_w);
    minions->red_count++;
    initWave(&minions->blue_waves[bi], TEAM_BLUE, map_w);
    minions->blue_count++;
}

static bool waveAllDead(MinionWave *wave) {
    for (int i = 0; i < MINION_COUNT; i++)
        if (wave->minions[i].state != MINION_DEAD) return false;
    return true;
}

static bool inAttackRange(Minion *a, Minion *b) {
    int dx = (position_px(a->pos) + MINION_W / 2) - (position_px(b->pos) + MINION_W / 2);
    int dy = (position_py(a->pos) + MINION_H / 2) - (position_py(b->pos) + MINION_H / 2);
    return (dx * dx + dy * dy) <= (ATTACK_RANGE * ATTACK_RANGE);
}

static Minion *findNearestEnemy(Minion *m, Minions *minions) {
    MinionWave *enemy_waves = (m->team == TEAM_RED) ? minions->blue_waves : minions->red_waves;
    Minion *nearest = NULL;
    int min_dist = INT32_MAX;

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!enemy_waves[w].active) continue;
        for (int j = 0; j < MINION_COUNT; j++) {
            Minion *e = &enemy_waves[w].minions[j];
            if (e->state == MINION_DEAD) continue;
            int dx = (position_px(m->pos) + MINION_W / 2) - (position_px(e->pos) + MINION_W / 2);
            int dy = (position_py(m->pos) + MINION_H / 2) - (position_py(e->pos) + MINION_H / 2);
            int dist = dx * dx + dy * dy;
            if (dist < min_dist) {
                min_dist = dist;
                nearest = e; 
            }
        }
    }
    return nearest;
}

static void updateMinion(Minion *m, Minions *minions, int dir) {
    if (m->state == MINION_DEAD) return;
    if (m->hp <= 0) { m->state = MINION_DEAD; return; }

    Minion *target = findNearestEnemy(m, minions);

    if (target != NULL && inAttackRange(m, target)) {
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
    position_move(&m->pos, dir, 0, MINION_SPEED);
}

void minionsControllerInit(Minions *minions, int map_w) {
    spawnWavePair(minions, map_w);
}

void minionsUpdate(Minions *minions, int map_w, bool second_elapsed) {
    if (second_elapsed) {
        minions->spawn_timer--;
        if (minions->spawn_timer <= 0) {
            minions->spawn_timer = SPAWN_SECONDS;
            spawnWavePair(minions, map_w);
        }
    }

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!minions->red_waves[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++)
            updateMinion(&minions->red_waves[w].minions[i], minions, -1);
        if (waveAllDead(&minions->red_waves[w])) {
            minions->red_waves[w].active = false;
            minions->red_count--;
        }
    }

    for (int w = 0; w < MAX_WAVES; w++) {
        if (!minions->blue_waves[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++)
            updateMinion(&minions->blue_waves[w].minions[i], minions, +1);
        if (waveAllDead(&minions->blue_waves[w])) {
            minions->blue_waves[w].active = false;
            minions->blue_count--;
        }
    }
}

void minionsTakeHit(Minions *minions, Box attack_box, int damage, Team attacker_team) {
    MinionWave *enemy_waves = (attacker_team == TEAM_RED) ? minions->blue_waves : minions->red_waves;
    for (int w = 0; w < MAX_WAVES; w++) {
        if (!enemy_waves[w].active) continue;
        for (int i = 0; i < MINION_COUNT; i++) {
            Minion *m = &enemy_waves[w].minions[i];
            if (m->state == MINION_DEAD) continue;
            Box mb = {position_px(m->pos), position_py(m->pos), MINION_W, MINION_H};
            if (boxesOverlap(attack_box, mb)) m->hp -= damage;
        }
    }
}
