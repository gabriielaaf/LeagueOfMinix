#include "TowerViewer.h"
#include "../model/tower/TowerConfig.h"
#include "video.h"

void towerViewerDraw(Towers *towers) {
    if (!towers) return;

    Tower *t;
    int bar_w;

    t = &towers->blue;
    if (t->hp > 0) {
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos), TOWER_W, TOWER_H, 1);
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos) - 10, TOWER_W, 6, 8);
        bar_w = (t->hp * TOWER_W) / TOWER_HP;
        if (bar_w > 0)
            vg_draw_rectangle(position_px(t->pos), position_py(t->pos) - 10, bar_w, 6, 1);
    }

    t = &towers->red;
    if (t->hp > 0) {
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos), TOWER_W, TOWER_H, 4);
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos) - 10, TOWER_W, 6, 8);
        bar_w = (t->hp * TOWER_W) / TOWER_HP;
        if (bar_w > 0)
            vg_draw_rectangle(position_px(t->pos), position_py(t->pos) - 10, bar_w, 6, 4);
    }

    if (towers->blue.projectile.active)
        vg_draw_rectangle(position_px(towers->blue.projectile.pos) - 2,
                          position_py(towers->blue.projectile.pos) - 2, 4, 4, 1);

    if (towers->red.projectile.active)
        vg_draw_rectangle(position_px(towers->red.projectile.pos) - 2,
                          position_py(towers->red.projectile.pos) - 2, 4, 4, 4);
}
