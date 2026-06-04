#include "TowerViewer.h"
#include "../model/tower/TowerConfig.h"
#include "video.h"

TowerViewer *createTowerViewer(){
    TowerViewer *viewer = malloc(sizeof(TowerViewer));

    if (viewer == NULL) {
        return NULL;
    }

    viewer->hpBar = createHpBarViewer();
    if (!viewer->hpBar) {
        free(viewer);
        return NULL;
    }

    return viewer;
}

void destroyTowerViewer(TowerViewer *viewer) {
    if (viewer == NULL) {
        return;
    }

    destroyHpBarViewer(viewer->hpBar);
    free(viewer);
}


void towerViewerDraw(TowerViewer *viewer, Towers *towers) {
    if (!towers) return;

    

    Tower *t;
    t = &towers->blue;

    hpBarViewerDraw(viewer->hpBar,
                    position_px(t->pos), position_py(t->pos),
                    TOWER_W,
                    t->hp,
                    TOWER_HP);

    if (t->hp > 0) {
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos), TOWER_W, TOWER_H, 1);
    }

    t = &towers->red;

    hpBarViewerDraw(viewer->hpBar,
                    position_px(t->pos), position_py(t->pos),
                    TOWER_W,
                    t->hp,
                    TOWER_HP);

    if (t->hp > 0) {
        vg_draw_rectangle(position_px(t->pos), position_py(t->pos), TOWER_W, TOWER_H, 4);
    }

    if (towers->blue.projectile.active)
        vg_draw_rectangle(position_px(towers->blue.projectile.pos) - 2,
                          position_py(towers->blue.projectile.pos) - 2, 4, 4, 1);

    if (towers->red.projectile.active)
        vg_draw_rectangle(position_px(towers->red.projectile.pos) - 2,
                          position_py(towers->red.projectile.pos) - 2, 4, 4, 4);
}
