//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_AREA_H
#define JRPG_AREA_H

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
#include "Item.h"
#include "Menu.h"
#include "Collision.h"
#include "Lootable.h"
#include "Npc.h"

typedef struct _area
{
    Floor *floor;
    Floor *trees;
    Menu *loot_message;

    void (*destroy)(struct _area *);
    void (*create_assets)(struct _area *, struct SDL_Renderer *renderer, Collision *collidables, int *item_keys, int num_items, int *npc_keys, int num_npcs, int *loot_cords_x, int *loot_cords_y, int *npc_cords_x, int *npc_cords_y);
    char *(*render_area)(struct _area *, struct SDL_Renderer *, Hero *, Items *, char *);
    int (*check_wait_thread)(struct _area *);
    int area_map_width;
    int area_map_height;
    int map_w;
    int map_h;
    int area_key;
    int num_collidables;
    int num_npcs;
    Items *bag;
    Lootable **lootables;
    Npc **npcs;
} Area;

Area *CREATE_AREA(int area_key);
#endif //JRPG_FOREST_H
