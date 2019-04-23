
#ifndef JRPG_AREA_H
#define JRPG_AREA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"
#include "Render.h"
#include "Assets.h"
#include "Floor.h"
#include "Hero.h"
#include "Item.h"
#include "Menu.h"
#include "Collision.h"
#include "Lootable.h"
#include "Npc.h"
#include "Line.h"
#include "Atlas.h"
#include "Dialogue.h"

int handler_area(void *ptr);
typedef struct _area
{
    Floor *floor;
    Floor *trees;
    Menu *loot_message;

    void (*destroy)(struct _area *);

    void (*create_assets)(struct _area *, struct SDL_Renderer *renderer,
                          Collision *collidables, int *item_keys, int num_items,
                          int *npc_keys, int *npc_types, int num_npcs,
                          int *loot_cords_x, int *loot_cords_y, int *npc_cords_x, int *npc_cords_y);

    Dialogue *current_dialogue;
    void (*render_area)(struct _area *);
    Render_Q *(*set_q)(struct _area *this);
    int (*check_wait_thread)(struct _area *);
    int area_map_width;
    int area_map_height;
    int map_w;
    int map_h;
    int area_key;
    int num_collidables;
    int num_npcs;
    Item *bag;
    Item *party_bag;
    Lootable **lootables;
    Npc **npcs;
    int last_x;
    int last_y;
    int current_index;
    int last_index;
    int first_load;
    Render_Q *q;
    Hero *hero;
    Atlas *atlas;
    int in_message;
    int in_dialogue;
} Area;

Area *CREATE_AREA(int area_key, Hero *hero, Item *party_bag, Atlas *atlas);
#endif
