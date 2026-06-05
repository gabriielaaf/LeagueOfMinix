#include "TowerViewer.h"

TowerViewer *createTowerViewer(xpm_map_t xpm_blue, xpm_map_t xpm_red) {
    TowerViewer *viewer = malloc(sizeof(TowerViewer));

    if (viewer == NULL) {
        return NULL;
    }

    viewer->hpBar = createHpBarViewer();
    viewer->blue = spriteCreate(xpm_blue);
    viewer->red = spriteCreate(xpm_red);

    if (!viewer->hpBar || !viewer->blue || !viewer->red) {
        destroyTowerViewer(viewer);
        return NULL;
    }

    return viewer;
}

void destroyTowerViewer(TowerViewer *viewer) {
    if (viewer == NULL) {
        return;
    }

    if (viewer->hpBar) destroyHpBarViewer(viewer->hpBar);
    if (viewer->blue) spriteDestroy(viewer->blue);
    if (viewer->red) spriteDestroy(viewer->red);
    free(viewer);
}


void towerViewerDraw(TowerViewer *viewer, Towers *towers) {
    if (!viewer || !towers) return;

    Tower *t = &towers->blue;

    if (t->hp > 0) {
        spriteDraw(viewer->blue, position_px(t->pos), position_py(t->pos));
        hpBarViewerDraw(viewer->hpBar,
                        position_px(t->pos), position_py(t->pos),
                        TOWER_W, t->hp, TOWER_HP);
    }
    
    t = &towers->red;
    if (t->hp > 0) {
        spriteDraw(viewer->red, position_px(t->pos), position_py(t->pos));
        hpBarViewerDraw(viewer->hpBar,
                        position_px(t->pos), position_py(t->pos),
                        TOWER_W, t->hp, TOWER_HP);
    }

    if (towers->blue.projectile.active)
        vg_draw_rectangle(position_px(towers->blue.projectile.pos) - 2,
                          position_py(towers->blue.projectile.pos) - 2, 4, 4, 1);

    if (towers->red.projectile.active)
        vg_draw_rectangle(position_px(towers->red.projectile.pos) - 2,
                          position_py(towers->red.projectile.pos) - 2, 4, 4, 4);
}
