#pragma once

#include <stdlib.h>

#include "../model/state/shopBarState.h"

#include "../assets/buttons/buy_buttons.h"

#include "ButtonViewer.h"

#include "video.h"

/**
 * @brief Renderer for a single upgradeable bar in the shop.
 */
typedef struct {
    uint32_t border_color;
    uint32_t empty_color;
    uint32_t fill_color;
    uint32_t buy_hover_color;
    uint32_t buy_disabled_color;
    ButtonViewer *buttonViewer;
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
