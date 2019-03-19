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

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _create_assets(Area *this, struct SDL_Renderer *renderer, Collision *collidables, int *item_keys, int num_items, int *collidable_cords_x, int *collidable_cords_y)
{
    this->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->floor->set_texture(this->floor, renderer, "graphics/map.png");
    this->trees->set_texture(this->trees, renderer, "graphics/forest.png");

    this->bag->fill_bag(this->bag, item_keys, NULL, num_items);
    this->lootables = (Lootable **)malloc(sizeof(Lootable *) * num_items);
    for (int k = 0; k < num_items; k++)
    {
        this->lootables[k] = CREATE_LOOTABLE(renderer, collidable_cords_x[k], collidable_cords_y[k], k, item_keys[k]);
    }
    collidables->add_collision(collidables, this->lootables, num_items, num_items, this->area_key);
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

    this->floor->render_floor(this->floor, renderer);
    hero->render(hero, renderer);
    for (int k = 0; k < this->bag->items_in_bag; k++)
    {
        this->lootables[k]->render(this->lootables[k], renderer);
    }
    this->trees->render_floor(this->trees, renderer);

    return dungeon_message;
}

Area *CREATE_FOREST(int area_key)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->create_assets = _create_assets;
    this->render_area = _render_area;

    this->bag = CREATE_BAG();

    this->map_w = 2048;
    this->map_h = 1792;
    this->area_key = area_key;
    this->destroy = _destroy;

    return this;
}
