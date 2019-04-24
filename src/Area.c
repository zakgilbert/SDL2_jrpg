
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
    ENQUEUE(this->q, this->floor, render_floor, NULL);
    ENQUEUE(this->q, this->hero, render_hero, NULL);

    for (i = 0; i < this->bag->items_in_bag; i++)
    {
        ENQUEUE(this->q, this->lootables[i], render_lootable, NULL);
    }
    for (i = 0; i < this->num_npcs; i++)
    {
        ENQUEUE(this->q, this->npcs[i], render_npc, NULL);
    }
    ENQUEUE(this->q, this->trees, render_floor, NULL);
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

static void _render_area(Area *this)
{
    int i, k;
    srand(time(NULL));
    if (CANCEL())
    {
        state = MAIN_MENU;
        previous_state = this->area_key;
        this->q->free(this->q);
        this->first_load = 1;

        return;
    }
    else if (!this->in_dialogue && !this->in_message &&
             NUM_STEPS > (200 + (rand() % 500)))
    {
        state = BATTLE;
        previous_state = this->area_key;
        ROLL = rand() % 3;
        this->q->free(this->q);
        this->first_load = 1;

        return;
    }
    else if (this->first_load)
    {
        this->q = this->set_q(this);
        this->first_load = 0;
        ROLL = -1;
        MOVEMENT_DISABLED = 0;
    }
    int item_to_be_obtained = -1;
    int npc_to_interact_with = -1;

    this->hero->animate(this->hero);
    if (!this->in_message || !this->in_dialogue)
    {
        for (k = 0; k < this->bag->items_in_bag; k++)
        {
            Lootable *current_lootable = this->lootables[k];
            if (current_lootable->ready_to_interact && !MOVEMENT_DISABLED)
            {
                item_to_be_obtained = current_lootable->loot(current_lootable);
                if (item_to_be_obtained != -1)
                {
                    this->party_bag->loot(this->party_bag, item_to_be_obtained);
                    
                    Line *line =
                        CREATE_LINE_WINDOW(this->atlas,
                                           ITEMS[item_to_be_obtained],
                                           WINDOW_WIDTH / 2, 10);

                    ENQUEUE(this->q, line, render_line, NULL);
                    this->in_message = 1;
                    this->last_x = X;
                    this->last_y = Y;
                }
            }
        }
    }
    if (NULL == this->current_dialogue)
    {
        for (i = 0; i < this->num_npcs; i++)
        {
            Npc *current_npc = this->npcs[i];
            if (current_npc->ready_to_interact)
            {
                npc_to_interact_with = current_npc->interact(current_npc);
                if (npc_to_interact_with != -1)
                {
                    this->current_dialogue =
                        CREATE_DIALOGUE(this->atlas,
                                        (const char **)DIALOGUES[i]->list,
                                        ((WINDOW_WIDTH / 2) - (208 / 2)),
                                        (WINDOW_HEIGHT - 64), DIALOGUES[i]->num_items);
                    this->last_x = X;
                    this->last_y = Y;
                }
            }
        }
    }
    if (((this->in_message && ((CONFIRM())))) ||
        (this->last_x > X + 20 || this->last_x < X - 20 ||
         this->last_y > Y + 20 || this->last_y < Y - 20))
    {
        this->in_message = 0;
        this->q->free(this->q);
        this->set_q(this);
    }

    if (NULL != this->current_dialogue)
    {
        this->q->free(this->q);
        this->set_q(this);
        this->in_dialogue = this->current_dialogue->add_lines(this->current_dialogue, this->q);
        if (!this->in_dialogue ||
            this->last_x > X + 20 || this->last_x < X - 20 ||
            this->last_y > Y + 20 || this->last_y < Y - 20)
        {
            this->current_dialogue->destroy(this->current_dialogue);
            this->current_dialogue = NULL;
            this->in_dialogue = 0;
        }
    }
    this->q->copy(this->q);
}

Area *CREATE_AREA(int area_key, Hero *hero, Item *party_bag, Atlas *atlas)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->destroy = _destroy;
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
    this->last_x = X;
    this->last_y = Y;
    this->first_load = 1;
    this->hero = hero;
    this->atlas = atlas;
    this->in_message = 0;
    this->in_dialogue = 0;
    this->q = CREATE_RENDER_Q();
    this->current_dialogue = NULL;

    return this;
}
