#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#include "actions.h"
#include "world.h"

int cpt_bombes;
struct bombe_s bombes[100];

void actions_init()
{
    cpt_bombes = 0;
    bombes = {0};
}

void actions_do(t_player *p_player, enum action act_id)
{
    if (p_player->credits > 0)
    {
        switch (act_id)
        {
        case ACTION_MOVE_L:

            p_player->x--;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_MOVE_R:

            p_player->x++;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_MOVE_U:

            p_player->y--;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_MOVE_D:

            p_player->y++;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_STILL:
            // Ne rien faire
            break;

        case ACTION_DASH_L:
            for (int i = 0; i < 5; i++)
            {
                p_player->x--;
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;
            break;

        case ACTION_DASH_R:
            for (int i = 0; i < 5; i++)
            {
                p_player->x++;
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;
            break;

        case ACTION_DASH_U:
            for (int i = 0; i < 5; i++)
            {
                p_player->y--;
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;
            break;

        case ACTION_DASH_D:
            for (int i = 0; i < 5; i++)
            {
                p_player->y++;
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;
            break;

        case ACTION_BOMB:
            p_player->credits -= BOMB_COST;
            bombes[cpt_bombes].id = cpt_bombes;
            bombes[cpt_bombes].couleur = p_player->id;
            bombes[cpt_bombes].x = p_player->x;
            bombes[cpt_bombes].y = p_player->y;
            bombes[cpt_bombes].meche = BOMB_TIMER;
            cpt_bombes++;
            break;
        }

        //******************** Code de la gestion des bombes **************
        for (int i = 0; i < cpt_bombes+1; i++)
        {
            if (bombes[i].meche == 0)
            {
                // Kaboouum !!!
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        world_paint_spot(bombes[i].x-1+j, bombes[i].y-1+k, bombes[i].color);
                    }
                }
                bombes[i].meche = 99; // Bombe deja pete donc set à valeur interdite
            }
            else if (bombes[i].meche <= BOMB_TIMER)
            {
                bombes[i].meche--;
            }
        }

        /*
        ACTION_STILL,
        ACTION_MOVE_L,
        ACTION_MOVE_R,
        ACTION_MOVE_U,
        ACTION_MOVE_D,
        ACTION_DASH_L,
        ACTION_DASH_R,
        ACTION_DASH_U,
        ACTION_DASH_D,
        ACTION_TELEPORT_L,
        ACTION_TELEPORT_R,
        ACTION_TELEPORT_U,
        ACTION_TELEPORT_D,
        ACTION_SPLASH,
        ACTION_BOMB,
        ACTION_NUMBER
        */
    }
}