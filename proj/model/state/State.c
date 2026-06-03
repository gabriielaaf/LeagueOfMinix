#include <lcom/lcf.h>

#include "State.h"

bool stateInit(State *state) {
    if (state == NULL) return false;

    state->state = STATE_MENU;
    state->running = true;
    state->winner = 0;

    state->game = gameStateCreate();
    if (state->game == NULL) {
        return false;
    }

    state->menu = menuStateCreate();
    if (state->menu == NULL) {
        gameStateDestroy(state->game);
        state->game = NULL;
        return false;
    }

    return true;
}

void stateDestroy(State *state) {
    if (state == NULL) return;

    if (state->game != NULL) {
        gameStateDestroy(state->game);
        state->game = NULL;
    }
}

void gameStart(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
    state->winner = 0;
}

void gamePause(State *state) {
    if (state == NULL) return;

    state->state = STATE_PAUSED;
}

void gameResume(State *state) {
    if (state == NULL) return;

    state->state = STATE_PLAYING;
}

void gameOver(State *state, int winner) {
    if (state == NULL) return;

    state->state = STATE_GAME_OVER;
    state->winner = winner;
}

void gameQuit(State *state) {
    if (state == NULL) return;

    state->running = false;
}

void stateStep(State *state, KeyboardState *kbd, MouseState *mouse) {
    if (state == NULL || kbd == NULL || mouse == NULL) return;

    if (kbd->exit) {
        gameQuit(state);
        return;
    }

    switch (state->state) {
       case STATE_MENU:
            menuStateStep(state->menu, kbd, mouse);

            if (menuStateShouldStart(state->menu)) {
                menuStateReset(state->menu);
                gameStart(state);
            }

            break;

        case STATE_PLAYING:
            gameStateStep(state->game, kbd, mouse);
            break;

        case STATE_PAUSED:
            break;

        case STATE_GAME_OVER:
            break;
    }
}
