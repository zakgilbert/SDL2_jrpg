#ifndef JRPG_COLLIDABLE_H
#define JRPG_COLLIDABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "header.h"

typedef struct _collidable
{
void (*destroy)(struct _collidable *);
struct SDL_Rect rect;

}Collidable;

Collidable * CREATE_COLLISION();
#endif