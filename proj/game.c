#include "game.h"

void game_init(Game *game) {
    game->state = GAME_STATE_MENU;
    game->running = true;
    game->winner = 0;
}



void game_update(Game *game) {
    switch (game->state) {
        case GAME_STATE_MENU:
            game_update_menu(game);
            break;

        case GAME_STATE_PLAYING:
            game_update_playing(game);
            break;

        case GAME_STATE_PAUSED:
            game_update_paused(game);
            break;

        case GAME_STATE_GAME_OVER:
            game_update_game_over(game);
            break;
    }
}

static void game_update_menu(Game* game){

    return;
}



static void game_update_playing(Game* game){


    return;
}


static void game_update_paused(Game *game){


    return;
}

static void game_update_game_over(Game *game){


    return;
}