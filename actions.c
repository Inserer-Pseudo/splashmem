#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#include "actions.h"
#include "world.h"

actions_init()
{
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
            if (p_player->y >= MAP_SIZE)
            {
                p_player->y = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_MOVE_D:

            p_player->y++;
            if (p_player->y >= MAP_SIZE)
            {
                p_player->y = 0;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 1;

            break;

        case ACTION_STILL:

            p_player->credits -= 1;

            break;

        case ACTION_DASH_L:

            for (int i = 0; i < 8; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 10;

            break;

        case ACTION_DASH_R:

            for (int i = 0; i < 8; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 10;

            break;

        case ACTION_DASH_U:

            for (int i = 0; i < 8; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 10;

            break;

        case ACTION_DASH_D:

            for (int i = 0; i < 8; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= 10;

            break;

        case ACTION_SPLASH:

            uint32_t cordX = 0;
            uint32_t cordY = 0;

            for (cordX = p_player->x - 1; cordX <= p_player->x + 1; cordX++)
            {
                for (cordY = p_player->y - 1; cordY < p_player->y + 1; cordY++)
                {
                    if (cordX >= MAP_SIZE)
                    {
                        cordX = 0;
                    }
                    else if (cordX < 0)
                    {
                        cordX = MAP_SIZE - 1;
                    }

                    if (cordY >= MAP_SIZE)
                    {
                        ordY = 0;
                    }
                    else if (cordY < 0)
                    {
                        cordY = MAP_SIZE - 1;
                    }
                    world_paint_spot(cordX, cordY, p_player->id);
                }

                p_player->credits -= 8;
            }
        }

        break;

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