#include "ChampionViewer.h"
#include <stdlib.h>

ChampionViewer *createChampionViewer(AnimSprite **animations, int numAnimations) {
    if (animations == NULL || numAnimations <= 0) {
        return NULL;
    }

    ChampionViewer *viewer = malloc(sizeof(ChampionViewer));

    if (viewer == NULL) {
        return NULL;
    }

    viewer->animations = animations;
    viewer->numAnimations = numAnimations;
    viewer->currentAnimation = 0;

    return viewer;
}

void destroyChampionViewer(ChampionViewer *viewer) {
    if (viewer == NULL) {
        return;
    }

    for (int i = 0; i < viewer->numAnimations; i++) {
        destroyAnimSprite(viewer->animations[i]);
    }

    free(viewer);
}

bool championViewerUpdate(ChampionViewer *viewer, Champion *champion) {
    if (viewer == NULL || champion == NULL) {
        return false;
    }

    int targetAnimation;
    ChampionState state = championGetState(champion);
    Direction dir = championGetDir(champion);

    switch (state) {
        case CHAMPION_MOVING:
            targetAnimation = (int)dir + 16;
            break;
        case CHAMPION_ATTACKING:
            targetAnimation = (int)dir + 8;
            break;
        default:
            targetAnimation = (int)dir;
            break;
    }

    if (viewer->currentAnimation != targetAnimation) {
        viewer->currentAnimation = targetAnimation;
        animSpriteReset(viewer->animations[targetAnimation]);
    }

    updateAnimSprite(viewer->animations[viewer->currentAnimation]);

    return animSpriteHasLooped(viewer->animations[viewer->currentAnimation]);
}

int championDraw(ChampionViewer *viewer, Champion *champion) {
    if (viewer == NULL || champion == NULL || championGetHp(champion) <= 0) {
        return 0;
    }

    Position pos = championGetPos(champion);

    setAnimSpritePosition(
        viewer->animations[viewer->currentAnimation],
        position_px(pos),
        position_py(pos)
    );

    return drawAnimSprite(viewer->animations[viewer->currentAnimation]);
}
