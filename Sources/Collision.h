#ifndef JRPG_COLLISION_H
#define JRPG_COLLISION_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Lootable.h"
#include "Words.h"

struct Collidable
{
    struct SDL_Rect *rect;
    int x, y;
    int index;
};

typedef struct _collision
{
    void (*destroy)(struct _collision *);
    void (*add_collision)(struct _collision *, Lootable **lootables, int num_lootables, int num_collidables, int area_key);
    void (*add_lootables)(struct _collision *, Lootable **lootables, int num_lootables, int area_key);
    void (*update_collidables)(struct _collision *, int area_key);
    
    struct Collidable ***collidables;
    int *num_collibables;
    int current_index;
} Collision;

Collision *CREATE_COLLISION();
#endif