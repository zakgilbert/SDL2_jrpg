
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

int get_middle_x(int, int);
int get_middle_y(int, int);

int time_to_animate();

typedef struct _Hero
{
    void (*destroy)(struct _Hero *);

    void (*set_texture)(struct _Hero *, struct SDL_Renderer *, char *);

    void (*render)(struct _Hero *, struct SDL_Renderer *);

    struct SDL_Rect *(*get_rect_pointer)(struct _Hero *);

    struct SDL_Rect *(*get_rect_pos_pointer)(struct _Hero *);

    void (*animate)(struct _Hero *);

    void (*check_direction)(struct _Hero *);

    void (*animate_down)(struct _Hero *);

    void (*animate_up)(struct _Hero *);

    void (*animate_left)(struct _Hero *);

    void (*animate_right)(struct _Hero *);

    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    struct SDL_Rect rect_pos;

} Hero;

Hero *CREATE_HERO();

void render_hero(void *obj, struct SDL_Renderer *renderer);
#endif
