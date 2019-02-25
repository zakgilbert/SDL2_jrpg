//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_FLOOR_H
#define JRPG_FLOOR_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Hero.h"
#include "header.h"


typedef struct __floor
{
    struct SDL_Texture *texture;

    void (*set_texture)(struct __floor *, struct SDL_Renderer *, char *);

    struct SDL_Rect rect;
    int tex_width;
    int tex_height;
    void (*destroy)(struct __floor *);

    struct SDL_Rect * (*get_rect_pointer) (struct __floor *);

    void (*render_floor) (struct __floor *, struct SDL_Renderer *);

} Floor;

Floor *create_floor(int, int, int, int);

#endif //JRPG_FLOOR_H
