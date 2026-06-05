#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "../Button.h"

/** @brief Maximum upgrade level for a shop bar. */
#define SHOP_BAR_MAX_LEVEL 5

/**
 * @brief State for a single upgradeable bar in the shop.
 */
typedef struct {
    int x;       /**< Left edge of the bar in pixels. */
    int y;       /**< Top edge of the bar in pixels. */
    int width;   /**< Width of the bar in pixels. */
    int height;  /**< Height of the bar in pixels. */
    int level;   /**< Current upgrade level (0 to SHOP_BAR_MAX_LEVEL). */
    ButtonState *buyButton; /**< Button that purchases the next level. */
} ShopBarState;

/**
 * @brief Allocates and positions a ShopBarState at the given coordinates.
 * @param x Left edge of the bar in pixels.
 * @param y Top edge of the bar in pixels.
 * @return Pointer to the new ShopBarState, or NULL on allocation failure.
 */
ShopBarState *shopBarStateCreate(int x, int y);

/**
 * @brief Frees a ShopBarState and its buy button.
 * @param bar ShopBarState to destroy.
 */
void shopBarStateDestroy(ShopBarState *bar);

/**
 * @brief Increments the upgrade level by one (no-op if already at max).
 * @param bar ShopBarState to upgrade.
 */
void shopBarStateBuy(ShopBarState *bar);

/**
 * @brief Returns true if the bar has reached the maximum upgrade level.
 * @param bar ShopBarState to check.
 * @return true when level == SHOP_BAR_MAX_LEVEL.
 */
bool shopBarStateIsMaxed(ShopBarState *bar);

/**
 * @brief Clears the one-frame click flag on the buy button.
 * @param bar ShopBarState to reset.
 */
void shopBarStateResetClick(ShopBarState *bar);
