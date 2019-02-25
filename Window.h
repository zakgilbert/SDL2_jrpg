//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_WINDOW_H
#define JRPG_WINDOW_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "header.h"

typedef struct __window
{
    void (*destroy) (struct __window *);

    void (*create_borders) (struct __window *, int, struct SDL_Rect *);

    struct SDL_Rect border_1;
    struct SDL_Rect border_2;
    struct SDL_Rect border_3;
    struct SDL_Rect border_4;

    struct SDL_Rect rect;
    int original_width;

    void (*render) (struct __window *, struct SDL_Renderer *);

} Window;

Window *CREATE_WINDOW (int, int, int, int);

#endif //JRPG_WINDOW_H
