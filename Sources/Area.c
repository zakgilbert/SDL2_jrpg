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

static void _create_assets(Area *this, struct SDL_Renderer *renderer)
{
    this->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->floor->set_texture(this->floor, renderer, "graphics/map.png");
    this->trees->set_texture(this->trees, renderer, "graphics/forest.png");
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
    this->trees->render_floor(this->trees, renderer);

    return dungeon_message;
}


Area *CREATE_FOREST(int num_chests, int area_key)
{
    Area *this = (Area *)malloc(sizeof(*this));

    this->create_assets = _create_assets;
    this->render_area = _render_area;


    this->map_w = 2048;
    this->map_h = 1792;
    this->area_key = area_key;
    this->destroy = _destroy;

    return this;
}
