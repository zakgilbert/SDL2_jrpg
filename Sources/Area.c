//

// Created by zachary on 1/23/19.
//

#include "Area.h"

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};
static void _destroy(Area *this)
{
    this->floor->destroy(this->floor);
    this->trees->destroy(this->trees);
    free(this->loot_cords_x);
    free(this->loot_cords_y);
    this->loot->destroy(this->loot);
    int i;

    for (i = 0; i < this->num_chests; i++)
    {
        this->loot_collidables[i]->destroy(this->loot_collidables[i]);
    }

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _create_assets(Area *this, struct SDL_Renderer *renderer)
{
    this->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->floor->set_texture(this->floor, renderer, "graphics/map.png");
    this->trees->set_texture(this->trees, renderer, "graphics/forest.png");
    this->create_loot(this, renderer);
    this->loot_collidables[0]->number_of_collidables = this->num_chests;
    this->create_npcs(this, renderer);
    this->npc_collidables[0]->number_of_collidables = 1;
}

static void _render_loot(Area *this, struct SDL_Renderer *renderer)
{
    int i;

    for (i = 0; i < this->num_chests; i++)
    {
        SDL_RenderCopy(renderer, this->loot_collidables[i]->first_texture, NULL, &this->loot_collidables[i]->rect_1);
    }
}
static char *_render_area(Area *this, struct SDL_Renderer *renderer, Hero *hero, Items *bag, char *dungeon_message)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        previous_state = this->area_key;
        INPUT = NONE;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        return dungeon_message;
    }
    int item_to_be_obtained = -1;

    MOVEMENT_DISABLED = 0;
    hero->animate(hero);

    if ((-1) != (item_to_be_obtained = this->loot_collidables[0]->collistion(this->loot_collidables)))
    {
        strcpy(dungeon_message, "LOOTED ");
        strcat(dungeon_message, ((const char *)bag->loot(bag, this->loot->get_enum(this->loot, item_to_be_obtained))));
        printf("\n(");
        for (int k = 0; k < 4; k++)
        {
            printf(" %d,", bag->item_quantities[k]);
        }
        refresh_inputs(USER_INPUTS, 6, 1);
        previous_state = this->area_key;
        state = MESSAGE;
    }
    this->npc_collidables[0]->collistion(this->npc_collidables);
    this->floor->render_floor(this->floor, renderer);
    hero->render(hero, renderer);
    this->loot_collidables[0]->render_collidables(this->loot_collidables, this->npc_collidables, renderer);
    this->trees->render_floor(this->trees, renderer);

    return dungeon_message;
}

static void _randomize_loot_locations(Area *this, int *x, int *y)
{
    int neg = 1;

    if (rand() % 1)
    {
        neg = -1;
    }

    *x = (rand() % (this->map_w - WINDOW_WIDTH)) * neg;
    *y = (rand() % (this->map_h - WINDOW_HEIGHT)) * (neg * neg);
}

static int _create_loot(Area *this, struct SDL_Renderer *renderer)
{
    int i, rand_index, rand_x, rand_y;
    this->loot = CREATE_BAG();
    this->loot->items = malloc(sizeof(char *) * this->num_chests);
    this->loot_cords_x = malloc(sizeof(int) * this->num_chests);
    this->loot_cords_y = malloc(sizeof(int) * this->num_chests);
    this->loot_collidables = malloc(sizeof(Collidable *) * this->num_chests);

    rand_index = 0;;
    rand_x = 0;
    rand_y = 0;

    for (i = 0; i < this->num_chests; i++)
    {
        this->randomize_loot_locations(this, &rand_x, &rand_y);
        this->loot_cords_x[i] = rand_x;
        this->loot_cords_y[i] = rand_y;
        rand_index = (rand() % ITEM_QUANTITY);
        this->loot->items[i] = malloc(strlen(ITEMS[rand_index]) + 1);
        strcpy(this->loot->items[i], ITEMS[rand_index]);
        this->loot_collidables[i] = CREATE_COLLIDABLE(CHEST);
        this->loot_collidables[i]->make_chest(this->loot_collidables[i], renderer, rand_x, rand_y, 16, 16);
        printf("\nAdding %s to area loot collection. at index %d.", this->loot->items[i], i);
    }
    return this->num_chests;
}
static void _create_npcs(Area *this, struct SDL_Renderer *renderer)
{
    int i;
    this->npc_collidables = malloc(sizeof(Collidable *) * this->num_npcs);
    this->loot_cords_x = malloc(sizeof(int) * this->num_npcs);
    this->loot_cords_y = malloc(sizeof(int) * this->num_npcs);

    for (i = 0; i < this->num_npcs; i++)
    {
        this->loot_cords_x[i] = 350;
        this->loot_cords_y[i] = 350;
        this->npc_collidables[i] = CREATE_COLLIDABLE(NPC);
        this->npc_collidables[i]->make_npc(this->npc_collidables[i], renderer, this->loot_cords_x[i], this->loot_cords_y[i], 72, 111, "graphics/giga.png");
    }
}
Area *CREATE_FOREST(int num_chests, int area_key)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->create_assets = _create_assets;
    this->render_area = _render_area;
    this->create_loot = _create_loot;
    this->render_loot = _render_loot;
    this->randomize_loot_locations = _randomize_loot_locations;
    this->create_npcs = _create_npcs;

    this->npc_collidables = NULL;
    this->num_npcs = 1;

    this->loot = NULL;
    this->loot_collidables = NULL;
    this->num_chests = num_chests;
    this->loot_cords_x = NULL;
    this->loot_cords_y = NULL;
    this->map_w = 2048;
    this->map_h = 1792;
    this->area_key = area_key;
    this->destroy = _destroy;

    return this;
}
