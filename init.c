#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <dlfcn.h>

#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"

uint32_t colors[MAX_PLAYERS + 1] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
    colors[1] = SDL_MapRGB(format, 0xFF, 0, 0);
    colors[2] = SDL_MapRGB(format, 0, 0xFF, 0);
    colors[3] = SDL_MapRGB(format, 0, 0x0, 0xFF);
    colors[4] = SDL_MapRGB(format, 0xFF, 0, 0xFF);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void inits(int argc, char *argv[])
{
    char *p1so = argv[1];
    char *p2so = argv[2];
    char *p3so = argv[3];
    char *p4so = argv[4];

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);
    SDL_PixelFormat *format = screenSurface->format;
    init_colors(format);

    void *p1sopen = dlopen(p1so, RTLD_LAZY);
    void *p2sopen = dlopen(p2so, RTLD_LAZY);
    void *p3sopen = dlopen(p3so, RTLD_LAZY);
    void *p4sopen = dlopen(p4so, RTLD_LAZY);

    actions_init();
    world_create_players();

    players[0]->get_action = dlsym(p1sopen, "get_action");
    players[1]->get_action = dlsym(p2sopen, "get_action");
    players[2]->get_action = dlsym(p3sopen, "get_action");
    players[3]->get_action = dlsym(p4sopen, "get_action");

    printf("inits done\n");
}