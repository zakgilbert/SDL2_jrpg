//
// Created by zachary on 1/23/19.
//

#include "Forest.h"

static const char * ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)
};
static void __destroy(Forest *this)
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

static void __create_assets(Forest *this, struct SDL_Renderer *renderer)
{
    this->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->floor->set_texture(this->floor, renderer, "graphics/map.png");
    this->trees->set_texture(this->trees, renderer, "graphics/forest.png");
    this->create_loot(this, renderer);
    this->loot_collidables[0]->number_of_collidables = this->num_chests;
}

static void __render_loot(Forest *this, struct SDL_Renderer *renderer)
{
    int i;

    for (i = 0; i < this->num_chests; i++)
    {
        SDL_RenderCopy(renderer, this->loot_collidables[i]->first_texture, NULL, &this->loot_collidables[i]->rect_1);
    }
}
static char *__render_forest(Forest *this, struct SDL_Renderer *renderer, Hero *hero, Items *bag, char *dungeon_message)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        previous_state = DARK_FOREST;
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
        for(int k = 0; k < 4; k++)
        {
            printf(" %d,", bag->item_quantities[k]);
        }
        refresh_inputs(inputs, 6, 1);
        previous_state = DARK_FOREST;
        state = MESSAGE;
    }

    this->floor->render_floor(this->floor, renderer);
    this->loot_collidables[0]->render_collidables(this->loot_collidables, renderer, this->floor->rect.x, this->floor->rect.y);
    hero->render(hero, renderer);
    this->trees->render_floor(this->trees, renderer);

    return dungeon_message;
}

static void _randomize_loot_locations(Forest * this, int * x, int * y)
{
    int neg = 1;

    if(rand() % 1)
    {
        neg = -1;
    }

    *x = (rand() % (this->map_w - WINDOW_WIDTH)) * neg;
    *y = (rand() % (this->map_h - WINDOW_HEIGHT)) * (neg * neg);

}

static int __create_loot(Forest *this, struct SDL_Renderer *renderer)
{
    int i, rand_index, rand_x, rand_y;
    this->loot = CREATE_BAG();
    this->loot->items = malloc(sizeof(char *) * this->num_chests);
    this->loot_cords_x = malloc(sizeof(int) * this->num_chests);
    this->loot_cords_y = malloc(sizeof(int) * this->num_chests);
    this->loot_collidables = malloc(sizeof(Collidable *) * this->num_chests);

    rand_index = 0;
    rand_x  = 0;
    rand_y =  0;


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
        printf("\nAdding %s to forest loot collection. at index %d.", this->loot->items[i], i);
    }
    return this->num_chests;
}
Forest *CREATE_FOREST(int num_chests)
{
    Forest *this = (Forest *)malloc(sizeof(*this));

    this->create_assets = __create_assets;
    this->render_forest = __render_forest;
    this->create_loot = __create_loot;
    this->render_loot = __render_loot;
    this->randomize_loot_locations = _randomize_loot_locations;
    
    this->loot = NULL;
    this->loot_collidables = NULL;
    this->num_chests = num_chests;
    this->loot_cords_x = NULL;
    this->loot_cords_y = NULL;
    this->map_w = 2048;
    this->map_h = 1792;
    this->destroy = __destroy;

    return this;
}
