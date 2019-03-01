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
    struct SDL_Texture * (*create_collidable_texture)(struct SDL_Renderer *, const char *, struct SDL_Rect *);
    struct SDL_Rect * (*make_chest)(struct _collidable *, struct SDL_Renderer *, int, int, int, int);
    void (*create_treasure)(struct _collidable **, int *, int *, const char **, int);
    struct SDL_Rect rect_1;
    struct SDL_Rect rect_2;
    struct SDL_Texture *first_texture;
    struct SDL_Texture *second_texture;
    int x;
    int y;

} Collidable;

Collidable *CREATE_COLLIDABLE();
#endif