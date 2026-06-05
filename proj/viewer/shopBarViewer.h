#pragma once

#include <stdlib.h>

#include "../model/state/shopBarState.h"

#include "video.h"

/**
 * @brief Renderer for a single upgradeable bar in the shop.
 */
typedef struct {
    int dummy; /**< Reserved for future renderer state. */
} ShopBarViewer;

/**
 * @brief Allocates and initialises a ShopBarViewer.
 * @return Pointer to the new ShopBarViewer, or NULL on failure.
 */
ShopBarViewer *shopBarViewerCreate();

/**
 * @brief Frees a ShopBarViewer.
 * @param viewer ShopBarViewer to destroy.
 */
void shopBarViewerDestroy(ShopBarViewer *viewer);

/**
 * @brief Draws the upgrade bar and its buy button.
 * Filled segments reflect the current upgrade level; the buy button is greyed out at max level.
 * @param viewer ShopBarViewer (currently stateless).
 * @param bar ShopBarState providing position, level, and buy-button state.
 */
void shopBarViewerDraw(ShopBarViewer *viewer, ShopBarState *bar);
