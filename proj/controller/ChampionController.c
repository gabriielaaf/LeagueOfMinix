#include "ChampionController.h"

void championUpdate(Champion *champion, bool animationLooped) {
    if (champion == NULL) {
        return;
    }

    if (championGetHp(champion) <= 0) {
        int timer = championGetRespawnTimer(champion) - 1;
        championSetRespawnTimer(champion, timer);
        if (timer == 0) {
            championSetRespawnTimer(champion, ALIVE);
            championRespawn(champion);
        }
        return;
    }

    ChampionState state = championGetState(champion);
    if ((state == CHAMPION_ATTACKING || state == CHAMPION_MOVING) && animationLooped) {
        championSetState(champion, CHAMPION_IDLE);
    }
}

void championMove(Champion *champion1, Champion *champion2, int dx, int dy, int map_w, int map_h) {
    if (champion1 == NULL || championGetHp(champion1) <= 0) {
        return;
    }

    if (dx != 0 || dy != 0) {
        Direction dir;
        if (dx == 0 && dy < 0) dir = NORTH;
        else if (dx == 0 && dy > 0) dir = SOUTH;
        else if (dx > 0 && dy == 0) dir = EAST;
        else if (dx < 0 && dy == 0) dir = WEST;
        else if (dx > 0 && dy < 0) dir = NORTHEAST;
        else if (dx < 0 && dy < 0) dir = NORTHWEST;
        else if (dx > 0 && dy > 0) dir = SOUTHEAST;
        else dir = SOUTHWEST;

        championSetDir(champion1, dir);
        if (championGetState(champion1) == CHAMPION_IDLE) {
            championSetState(champion1, CHAMPION_MOVING);
        }
    }

    Position pos = championGetPos(champion1);
    Position next = pos;
    position_move(&next, dx, dy, championGetSpeed(champion1));
    int nx = position_px(next);
    int ny = position_py(next);
    int w = championGetWidth(champion1);
    int h = championGetHeight(champion1);

    if (nx < 0 || nx + w > map_w || ny < 0 || ny + h > map_h) {
        return;
    }

    if (champion2 != NULL && championGetHp(champion2) > 0) {
        Box b1 = championGetCollisionBox(champion1);
        b1.x += nx - position_px(pos);
        b1.y += ny - position_py(pos);
        Box b2 = championGetCollisionBox(champion2);
        if (boxesOverlap(b1, b2)) {
            return;
        }
    }

    championSetPos(champion1, next);
}

bool championAttack(Champion *champion) {
    if (champion == NULL || championGetState(champion) == CHAMPION_ATTACKING) {
        return false;
    }
    championSetState(champion, CHAMPION_ATTACKING);
    return true;
}

bool championHits(Champion *attacker, Champion *target) {
    if (attacker == NULL || target == NULL) {
        return false;
    }
    if (championGetHp(attacker) <= 0 || championGetHp(target) <= 0) {
        return false;
    }
    return championAttackHits(attacker, target);
}

void championDecreaseHp(Champion *target, int dmg) {
    if (target == NULL) {
        return;
    }
    championAddHp(target, -dmg);
    if (championGetHp(target) <= 0) {
        championSetRespawnTimer(target, RESPAWN_SECONDS);
        championClearPosition(target);
    }
}

void championUpgradeHp(Champion *champion) {
    if (champion == NULL) {
        return;
    }
    championAddHp(champion, 10);
}

void championUpgradeDamage(Champion *champion) {
    if (champion == NULL) {
        return;
    }
    championAddAttackDmg(champion, 5);
}

void championUpgradeSpeed(Champion *champion) {
    if (champion == NULL) {
        return;
    }
    championAddSpeed(champion, 1);
}
