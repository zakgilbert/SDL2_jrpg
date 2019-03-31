
#include "Area.h"

/**
 * Name:    Area.c    
 * Project: jrpg     
 * Author:  Zachary Gilbert
 * Description: 
 *      The Area class lets one create a new game area(dungeon, town, wilderness...)
 * 
 * Insights:
 *      CREATE_AREA(int area_key) lets you pass in an area key which comes from the 
 *      states enum list. The details of the area are futher specified when create_assets
 *      is called.
 * 
 *      Example:    Area *dark_forest = CREATE_AREA(DARK_FOREST);
 *                  dark_forest->create_assets(dark_forest, renderer,...,...)
 */

/* Generate the char** list of all items from the ITEMS_ENUM */
static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

/*
 * destroy
 * the Area struct
 */
static void _destroy(Area *this)
{
    this->floor->destroy(this->floor);
    this->trees->destroy(this->trees);

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _create_assets(Area *this, struct SDL_Renderer *renderer, Collision *collidables,
                           int *item_keys, int num_items, int *npc_keys, int *npc_types, int num_npcs,
                           int *loot_cords_x, int *loot_cords_y, int *npc_cords_x, int *npc_cords_y)
{
    int i, k;
    this->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->floor->set_texture(this->floor, renderer, "graphics/map.png");
    this->trees->set_texture(this->trees, renderer, "graphics/forest.png");

    this->bag->fill_bag(this->bag, item_keys, NULL, num_items);
    this->lootables = (Lootable **)malloc(sizeof(Lootable *) * num_items);
    this->npcs = (Npc **)malloc(sizeof(Npc *) * num_npcs);

    for (k = 0; k < num_items; k++)
    {
        this->lootables[k] = CREATE_LOOTABLE(renderer, loot_cords_x[k], loot_cords_y[k], k, item_keys[k]);
        this->num_collidables++;
    }
    for (i = 0; i < num_npcs; i++)
    {
        this->npcs[i] = CREATE_NPC(renderer, npc_cords_x[i], npc_cords_y[i], i, npc_keys[i], NPC_PATHS->list[npc_keys[i]], npc_types[i]);
        this->num_npcs++;
        this->num_collidables++;
    }
    collidables->add_collision(collidables, this->lootables, num_items, this->npcs, num_npcs, this->num_collidables, this->area_key);
}

static Message *_render_area(Area *this, struct SDL_Renderer *renderer, Hero *hero, Item *bag)
{
    int i, k;
    srand(time(NULL));
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        previous_state = this->area_key;
        INPUT = NONE;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        return NULL;
    }
  /*  else if (NUM_STEPS > (300 + (rand() % 500)))
    {
        state = BATTLE;
        previous_state = this->area_key;
        ROLL = rand() % 3;

        return NULL;
    } */
    int item_to_be_obtained = -1;
    int npc_to_interact_with = -1;

    Message *dungeon_message = NULL;
    MOVEMENT_DISABLED = 0;
    hero->animate(hero);

    this->floor->render_floor(this->floor, renderer);
    for (k = 0; k < this->bag->items_in_bag; k++)
    {
        if (this->current_index == -1 &&
            this->lootables[k]->ready_to_interact > 0 &&
            (0 <= ((item_to_be_obtained) = (this->lootables[k]->loot(this->lootables[k])))))
        {
            this->last_x = X;
            this->last_y = Y;
            this->current_index = k;
            dungeon_message = CREATE_MESSAGE((char *)ITEMS[item_to_be_obtained], 0, 0, 10, ONE_LINER, item_to_be_obtained);
            state = MESSAGE;
            previous_state = this->area_key;
            USER_INPUTS[4] = 0;
            bag->loot(bag, item_to_be_obtained);
        }
        this->lootables[k]->render(this->lootables[k], renderer);
    }
    for (i = 0; i < this->num_npcs; i++)
    {
        if (this->current_index == -1 &&
            this->npcs[i]->ready_to_interact != 0 &&
            (0 <= ((npc_to_interact_with) = (this->npcs[i]->interact(this->npcs[i])))))
        {
            this->last_x = X;
            this->last_y = Y;
            this->current_index = i;
            dungeon_message = CREATE_MESSAGE(" ", 0, 0, 10, DIALOGUE, npc_to_interact_with);
            state = MESSAGE;
            previous_state = this->area_key;
            WAITING_FOR_MESSAGE = 0;
            USER_INPUTS[4] = 0;
        }
        this->npcs[i]->render(this->npcs[i], renderer);
    }
    hero->render(hero, renderer);
    this->trees->render_floor(this->trees, renderer);
    if (this->current_index != -1 && (this->last_x != X || this->last_y != Y))
    {
        this->npcs[this->current_index]->ready_to_interact = 0;
        this->current_index = -1;
        this->last_x = X;
        this->last_y = Y;
    }
    return dungeon_message;
}

Area *CREATE_AREA(int area_key)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->create_assets = _create_assets;
    this->render_area = _render_area;

    this->bag = CREATE_BAG();
    this->num_collidables = 0;
    this->num_npcs = 0;
    this->map_w = 1239;
    this->map_h = 1024;
    this->area_key = area_key;
    this->destroy = _destroy;
    this->last_x = 0;
    this->last_y = 0;
    this->current_index = -1;
    this->last_index = -1;
    this->last_x = X;
    this->last_y = Y;
    return this;
}
