#ifndef JRPG_LOOTABLE_H
#define JRPG_LOOTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Graphics.h"

typedef struct _Lootable
{
    void (*destroy)(struct _Lootable *this);
    int (*loot)(struct _Lootable *this);
    struct _Lootable *(*render)(struct _Lootable *this, struct SDL_Renderer *renderer);

    struct SDL_Texture *texture;
    struct SDL_Texture *alt_tex;
    struct SDL_Rect rect;

    int key;
    int looted;
    int index;
    int x, y;
    int ready_to_interact;

} Lootable;

Lootable *CREATE_LOOTABLE(struct SDL_Renderer *renderer, int x, int y, int index, int key);
void render_lootable(void *obj, struct SDL_Renderer *renderer);

#endif