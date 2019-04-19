
#ifndef JRPG_HERO_H
#define JRPG_HERO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Sprite.h"

int get_middle_x(int, int);
int get_middle_y(int, int);

int time_to_animate();

typedef struct _Hero
{
    void (*destroy)(struct _Hero *);

    void (*render)(struct _Hero *, struct SDL_Renderer *);

    void (*animate)(struct _Hero *);

    void (*check_direction)(struct _Hero *);

    void (*animate_down)(struct _Hero *);

    void (*animate_up)(struct _Hero *);

    void (*animate_left)(struct _Hero *);

    void (*animate_right)(struct _Hero *);

    Sprite *sprite;
    int index;
    char *ani_buffer;
    int d_i;
    int u_i;
    int l_i;
    int r_i;
    enum direction
    {
        up,
        down,
        left,
        right
    } facing;

} Hero;

Hero *CREATE_HERO(Renderer renderer);

void render_hero(void *obj, struct SDL_Renderer *renderer);
#endif
