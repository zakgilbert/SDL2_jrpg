//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_FOREST_H
#define JRPG_FOREST_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Floor.h"
#include "Hero.h"
#include "header.h"
#include "Collidable.h"
#include "Item.h"
#include "Menu.h"

typedef struct __forest
{
    Floor *floor;
    Floor *trees;
    Menu *loot_message;

    void (*destroy)(struct __forest *);
    void (*create_assets)(struct __forest *, struct SDL_Renderer *);
    char *(*render_forest)(struct __forest *, struct SDL_Renderer *, Hero *, Items *, char *);
    int (*create_loot)(struct __forest *, struct SDL_Renderer *);
    void (*render_loot)(struct __forest *, struct SDL_Renderer *);
    int (*check_wait_thread)(struct __forest *);
    void (*randomize_loot_locations)(struct __forest *, int *x, int *y);
    int num_chests;
    int *loot_cords_x;
    int *loot_cords_y;
    Items *loot;
    Collidable **loot_collidables;
    int forest_map_width;
    int forest_map_height;
    int map_w;
    int map_h;

} Forest;

Forest *CREATE_FOREST(int);
#endif //JRPG_FOREST_H
