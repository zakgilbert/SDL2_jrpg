
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

int handler_area(void *ptr)
{
    Area *area = (Area *)ptr;
    area->render_area(area);
    return 1;
}
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

static Render_Q *_set_q(struct _area *this)
{
    int i;
    this->q->add(this->q, this->q->new_node(this->floor, render_floor, NULL));
    this->q->add(this->q, this->q->new_node(this->hero, render_hero, NULL));

    for (i = 0; i < this->bag->items_in_bag; i++)
    {
        this->q->add(this->q, this->q->new_node(this->lootables[i], render_lootable, NULL));
    }
    for (i = 0; i < this->num_npcs; i++)
    {
        this->q->add(this->q, this->q->new_node(this->npcs[i], render_npc, NULL));
    }
    this->q->add(this->q, this->q->new_node(this->trees, render_floor, NULL));
    this->first_load = 0;
    return this->q;
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

static Message *_render_area(Area *this)
{
    int i, k;
    srand(time(NULL));
    if (CANCEL())
    {
        state = MAIN_MENU;
        previous_state = this->area_key;
        this->q->free(this->q);
        this->first_load = 1;

        return NULL;
    }
    else if (NUM_STEPS > (200 + (rand() % 500)))
    {
        state = BATTLE;
        previous_state = this->area_key;
        ROLL = rand() % 3;
        this->q->free(this->q);
        this->first_load = 1;

        return NULL;
    }
    else if (this->first_load)
    {
        this->q = this->set_q(this);
        this->first_load = 0;
        ROLL = -1;
    }
    int item_to_be_obtained = -1;
    int npc_to_interact_with = -1;

    Message *dungeon_message = NULL;
    MOVEMENT_DISABLED = 0;
    this->hero->animate(this->hero);

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
            this->party_bag->loot(this->party_bag, item_to_be_obtained);
        }
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
        }
    }
    if (this->current_index != -1 && (this->last_x != X || this->last_y != Y))
    {
        this->npcs[this->current_index]->ready_to_interact = 0;
        this->current_index = -1;
        this->last_x = X;
        this->last_y = Y;
    }
    this->q->copy(this->q);
    return dungeon_message;
}

Area *CREATE_AREA(int area_key, Hero *hero, Item *party_bag)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->create_assets = _create_assets;
    this->render_area = _render_area;
    this->set_q = _set_q;
    this->bag = CREATE_BAG();
    this->party_bag = party_bag;
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
    this->first_load = 1;
    this->hero = hero;
    this->q = CREATE_RENDER_Q();

    return this;
}
