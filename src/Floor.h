
#ifndef JRPG_FLOOR_H
#define JRPG_FLOOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"

typedef struct _Floor
{
    struct SDL_Texture *texture;

    void (*set_texture)(struct _Floor *this, struct SDL_Renderer *renderer, char *path);

    struct SDL_Rect rect;
    int tex_width;
    int tex_height;
    void (*destroy)(struct _Floor *);

    void (*render)(struct _Floor *this, struct SDL_Renderer *renderer);

} Floor;

Floor *create_floor(int, int, int, int);

void render_floor(void *obj, struct SDL_Renderer *renderer);
#endif
