//
// Created by zachary on 1/23/19.
//

#include "Forest.h"

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
static void __render_forest(Forest *this, struct SDL_Renderer *renderer, Hero *hero, Items *bag)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        previous_state = DARK_FOREST;
        INPUT = NONE;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        return;
    }
    int item_to_be_obtained = -1;
    MOVEMENT_DISABLED = 0;
    hero->animate(hero);

    item_to_be_obtained = this->loot_collidables[0]->collistion(this->loot_collidables);

    if (item_to_be_obtained > -1 && this->loot_collidables[item_to_be_obtained]->chest_was_looted && INPUT == OKAY)
    {
        bag->add_item(bag, this->loot->get_enum(this->loot, item_to_be_obtained));
        WAITING_FOR_MESSAGE = this->loot->get_enum(this->loot, item_to_be_obtained);

        printf("\nCurrent State %d\nPrevious State", state, previous_state);
        previous_state = DARK_FOREST;
        state = MESSAGE;
        printf("\nCurrent State %d\nPrevious State", state, previous_state);
    }

    this->floor->render_floor(this->floor, renderer);
    this->loot_collidables[0]->render_collidables(this->loot_collidables, renderer, this->floor->rect.x, this->floor->rect.y);
    hero->render(hero, renderer);
    this->trees->render_floor(this->trees, renderer);
}

static int __create_loot(Forest *this, struct SDL_Renderer *renderer)
{
    int i, rand_index, rand_x, rand_y, lower_x, lower_y, upper_x, upper_y;
    this->loot = CREATE_BAG();
    this->loot->items = malloc(sizeof(char *) * this->num_chests);
    this->loot_cords_x = malloc(sizeof(int) * this->num_chests);
    this->loot_cords_y = malloc(sizeof(int) * this->num_chests);
    this->loot_collidables = malloc(sizeof(Collidable *) * this->num_chests);

    rand_index = 0;
    rand_x = 250;
    rand_y = 250;

    upper_x = this->forest_map_width - (WINDOW_WIDTH / 2);
    lower_x = this->forest_map_width + (WINDOW_WIDTH / 2);
    upper_y = this->forest_map_height - (WINDOW_HEIGHT / 2);
    lower_y = this->forest_map_height + (WINDOW_HEIGHT / 2);

    for (i = 0; i < this->num_chests; i++)
    {
        this->loot_cords_x[i] = rand_x;
        this->loot_cords_y[i] = rand_y;
        rand_index = (rand() % ITEM_QUANTITY);
        this->loot->items[i] = malloc(strlen(ITEMS[rand_index]) + 1);
        strcpy(this->loot->items[i], ITEMS[rand_index]);
        this->loot_collidables[i] = CREATE_COLLIDABLE(CHEST);
        this->loot_collidables[i]->make_chest(this->loot_collidables[i], renderer, rand_x, rand_y, 16, 16);
        printf("\nAdding %s to forest loot collection.", this->loot->items[i]);
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
    this->loot = NULL;
    this->loot_collidables = NULL;
    this->num_chests = num_chests;
    this->loot_cords_x = NULL;
    this->loot_cords_y = NULL;
    this->forest_map_width = 2048;
    this->forest_map_height = 1792;
    this->destroy = __destroy;

    return this;
}
