#ifndef JRPG_COLLIDABLE_H
#define JRPG_COLLIDABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"

struct edge
{
    int x_1;
    int y_1;
    int x_2;
    int y_2;
};

typedef struct _collidable
{
    void (*destroy)(struct _collidable *);
    struct SDL_Texture *(*create_collidable_texture)(struct SDL_Renderer *, const char *, struct SDL_Rect *);
    void (*render_collidables)(struct _collidable **chests, struct _collidable **npcs, struct SDL_Renderer *);
    int (*collistion)(struct _collidable **);
    int (*check_down_edge)(struct _collidable *);
    int (*check_up_edge)(struct _collidable *);
    int (*check_left_edge)(struct _collidable *);
    int (*check_right_edge)(struct _collidable *);
    int (*interact)(struct _collidable *);
    void (*update_collidables)(struct _collidable *);
    struct SDL_Rect rect_1;
    struct SDL_Rect rect_2;
    struct SDL_Texture *first_texture;
    struct SDL_Texture *second_texture;
    int x;
    int y;
    int x_ref;
    int y_ref;
    int number_of_collidables;
    int unlocked;

    struct edge left;
    struct edge right;
    struct edge bottem;
    struct edge top;
    int collision_padding_x;
    int collision_padding_y;

    enum COLLIDABLE_TYPES TYPE;
    /**
     * Lootable Item Section...chests and such.
     */
    struct SDL_Rect *(*make_chest)(struct _collidable *, struct SDL_Renderer *, int, int, int, int);
    int (*loot_chest)(struct _collidable *);
    int chest_was_looted;

    /**
     * NPC Section
     */

    void (*make_npc)(struct _collidable *, struct SDL_Renderer *, int, int, int, int, char *path);

} Collidable;

Collidable *CREATE_COLLIDABLE(int type);
#endif