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