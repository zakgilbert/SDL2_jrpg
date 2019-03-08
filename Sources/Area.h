//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_AREA_H
#define JRPG_AREA_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Floor.h"
#include "Hero.h"
#include "Collidable.h"
#include "Item.h"
#include "Menu.h"

typedef struct _area
{
    Floor *floor;
    Floor *trees;
    Menu *loot_message;

    void (*destroy)(struct _area *);
    void (*create_assets)(struct _area *, struct SDL_Renderer *);
    char *(*render_area)(struct _area *, struct SDL_Renderer *, Hero *, Items *, char *);
    int (*create_loot)(struct _area *, struct SDL_Renderer *);
    void (*render_loot)(struct _area *, struct SDL_Renderer *);
    int (*check_wait_thread)(struct _area *);
    void (*randomize_loot_locations)(struct _area *, int *x, int *y);
    void (*create_npcs)(struct _area *, struct SDL_Renderer *);
    int num_chests;
    int *loot_cords_x;
    int *loot_cords_y;
    Items *loot;
    Collidable **loot_collidables;
    Collidable **npc_collidables;
    int num_npcs;
    int area_map_width;
    int area_map_height;
    int map_w;
    int map_h;
    int area_key;

} Area;

Area *CREATE_FOREST(int, int area_key);
#endif //JRPG_FOREST_H
