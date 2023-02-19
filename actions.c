#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#include "action.h"

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
        p_player->credits -= 1;

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
}