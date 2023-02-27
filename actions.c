#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#include "actions.h"
#include "world.h"

int cpt_bombes;
struct bombe_s bombes[100];

uint32_t cordX = 0;
uint32_t cordY = 0;

void actions_init()
{
    cpt_bombes = 0;
    bombes[0].meche = 99; // Pour pas quelle pete des le debut
}

void actions_do(t_player *p_player, enum action act_id)
{
    if (p_player->credits > 0)
    {
        switch (act_id)
        {
        case ACTION_STILL:
            // Ne rien faire
            break;

        case ACTION_MOVE_L:

            if (p_player->x <= 0)
            {
                p_player->x = MAP_SIZE;
            }
            p_player->x--;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= MOVE_COST;
            break;

        case ACTION_MOVE_R:

            p_player->x++;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= MOVE_COST;

            break;

        case ACTION_MOVE_U:

            if (p_player->y <= 0)
            {
                p_player->y = MAP_SIZE;
            }
            p_player->y--;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= MOVE_COST;

            break;

        case ACTION_MOVE_D:

            if (p_player->y >= MAP_SIZE)
            {
                p_player->y = 0;
            }
            p_player->y++;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= MOVE_COST;

            break;

        case ACTION_TELEPORT_L:

            for (int i = 0; i < TP_SIZE; i++)
            {
                if (p_player->x <= 0)
                {
                    p_player->x = MAP_SIZE;
                }
                p_player->x--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= TP_COST;

            break;

        case ACTION_TELEPORT_R:

            for (int i = 0; i < TP_SIZE; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= TP_COST;

            break;

        case ACTION_TELEPORT_U:

            for (int i = 0; i < TP_SIZE; i++)
            {
                if (p_player->y <= 0)
                {
                    p_player->y = MAP_SIZE;
                }
                p_player->y--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= TP_COST;

            break;

        case ACTION_TELEPORT_D:

            for (int i = 0; i < TP_SIZE; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= TP_COST;

            break;

        case ACTION_DASH_L:

            for (int i = 0; i < DASH_SIZE; i++)
            {
                if (p_player->x <= 0)
                {
                    p_player->x = MAP_SIZE;
                }
                p_player->x--;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;

            break;

        case ACTION_DASH_R:

            for (int i = 0; i < DASH_SIZE; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x++;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;

            break;

        case ACTION_DASH_U:

            for (int i = 0; i < DASH_SIZE; i++)
            {
                if (p_player->y <= 0)
                {
                    p_player->y = MAP_SIZE;
                }
                p_player->y--;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= DASH_COST;

            break;

        case ACTION_DASH_D:

            for (int i = 0; i < DASH_SIZE; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y++;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= 10;

            break;

        case ACTION_SPLASH:

            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    uint32_t px = p_player->x - 1 + j;
                    uint32_t py = p_player->y - 1 + k;
                    if (px <= MAP_SIZE && py <= MAP_SIZE)
                    {
                        world_paint_spot(px, py, p_player->id);
                    }
                    else if (px > MAP_SIZE)
                    {
                        px = 1;
                        world_paint_spot(px, py, p_player->id);
                    }
                    else if (py > MAP_SIZE)
                    {
                        py = 1;
                        world_paint_spot(px, py, p_player->id);
                    }
                }
            }
            p_player->credits -= SPLASH_COST;
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

        case ACTION_NUMBER:
            break;

        default:
            printf("Action non reconnue");
            break;
        }

        //******************** Code de la gestion des bombes **************
        for (int i = 0; i < cpt_bombes; i++)
        {
            if (bombes[i].meche == 0)
            {
                // Kaboouum !!!
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        uint32_t px = bombes[i].x - 1 + j;
                        uint32_t py = bombes[i].y - 1 + k;
                        if (px <= MAP_SIZE && py <= MAP_SIZE)
                        {
                            world_paint_spot(px, py, bombes[i].couleur);
                        }
                        else if (px > MAP_SIZE)
                        {
                            px = 1;
                            world_paint_spot(px, py, bombes[i].couleur);
                        }
                        else if (py > MAP_SIZE)
                        {
                            py = 1;
                            world_paint_spot(px, py, bombes[i].couleur);
                        }
                    }
                }
                bombes[i].meche = 99; // Bombe deja pete donc set à valeur interdite
            }
            else if (bombes[i].meche <= BOMB_TIMER)
            {
                bombes[i].meche--;
            }
        }
    }
}
