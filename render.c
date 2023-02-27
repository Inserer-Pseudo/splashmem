#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

int pauvre = 0;
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_map()
{
    int i = 0;
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    screenSurface = SDL_GetWindowSurface(window);

    for (i = 0; i < SPOT_NUM; i++)
    {
        rect.x = (i % MAP_SIZE) * SQUARE_SIZE;
        rect.y = (i / MAP_SIZE) * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[mapmem[i]]);
    }
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(screenSurface);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_player()
{
    int i = 0;
    screenSurface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        rect.x = players[i]->x * SQUARE_SIZE;
        rect.y = players[i]->y * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[i] - 0x00202020);
    }
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(screenSurface);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void main_loop()
{
    // int is_game_finish = 0;   vous pouvez l'utilisez

    while (!quitting)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quitting = 1;
            }
        }

        /***************Deplacement des joueurs - code exemple a remplacer*/

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            world_do_player_action(players[i]);
        }

        // gestion fin de partie (si un joueur crédit=0 --> fin de partie)

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i]->credits <= 0)
            {
                pauvre++;
            }
        }

        if (pauvre != 0)
        {
            world_get_winner();
            sleep(5);
            quitting = 1;
        }

        /**************/

        //  Update de la map

        render_map();
        render_player();

        SDL_Delay(10);
    }
}
