
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

int get_middle (int, int);

int time_to_animate ();

typedef struct __hero
{
    void (*destroy) (struct __hero *);

    void (*set_texture) (struct __hero *, struct SDL_Renderer *, char *);

    void (*render) (struct __hero *, struct SDL_Renderer *);

    struct SDL_Rect *(*get_rect_pointer) (struct __hero *);

    struct SDL_Rect *(*get_rect_pos_pointer) (struct __hero *);

    void (*animate) (struct __hero *);

    void (*check_direction) (struct __hero *);

    void (*animate_down) (struct __hero *);

    void (*animate_up) (struct __hero *);

    void (*animate_left) (struct __hero *);

    void (*animate_right) (struct __hero *);


    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    struct SDL_Rect rect_pos;

} Hero;

Hero *CREATE_HERO ();

#endif 
