#include <stdlib.h>
#include <stdio.h>
#include<string.h>

#include "world.h"
#include "param.h"
#include "player.h"
#include "actions.h"
#include <dlfcn.h>
#include "param.h"




/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player* players[MAX_PLAYERS] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players()
{
    int i = 0;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        players[i] = (t_player*) malloc(sizeof(t_player));
        player_init(players[i], i);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
   actions_do(p_player, p_player->get_action());
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos] = num;
}



/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner()
{
    int winner = 0;
    int nb_pixels[MAX_PLAYERS];
    int pixels_max =0;

    for (int joueur=1; joueur <= MAX_PLAYERS; joueur++)
    {
        nb_pixels[joueur]=0; // init nombre cases peintes du joueur

        for (uint8_t pixel = 0; pixel<(MAP_SIZE*MAP_SIZE); pixel++)
        {
            if(mapmem[pixel]==joueur)
            {
                nb_pixels[joueur]++;
            }
        }

        if (nb_pixels[joueur] > pixels_max)
        {
            pixels_max = nb_pixels[joueur];
            winner = joueur;
        }
    }

    printf("le grand gagnant la partie splashmem est le joueur %d avec %d pixels de colorie, félicitation !\n", winner, nb_pixels);

}
