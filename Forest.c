//
// Created by zachary on 1/23/19.
//

#include "Forest.h"

static void __destroy(Forest *this)
{
    this->floor->destroy(this->floor);
    this->trees->destroy(this->trees);
    free(this->lewt_cords_x);
    free(this->lewt_cords_y);
    this->forest_lewt->destroy(this->forest_lewt);
    int i;

    for (i = 0; i < this->num_chests; i++)
    {
        this->treasure[i]->destroy(this->treasure[i]);        
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
    this->create_lewt(this, renderer);
}

static void __render_lewt(Forest *this, struct SDL_Renderer *renderer)
{
    int i;

    for(i = 0; i < this->num_chests; i++)
    {
        SDL_RenderCopy(renderer, this->treasure[i]->first_texture, NULL, &this->treasure[i]->rect_1);
        
        this->treasure[i]->rect_1.x = this->treasure[i]->x - this->floor->rect.x;
        this->treasure[i]->rect_1.y = this->treasure[i]->y - this->floor->rect.y; 
        //printf("\nchest %d is located at \(%d, %\d).", i, this->treasure[i]->rect_1.x, this->treasure[i]->rect_1.y);
    }
}
static void __render_forest(Forest *this, struct SDL_Renderer *renderer, Hero *hero)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        previous_state = DARK_FOREST;
        INPUT = NONE;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        return;
    }
    MOVEMENT_DISABLED = 0;
    hero->animate(hero);
    this->floor->render_floor(this->floor, renderer);
    this->render_lewt(this, renderer);
    hero->render(hero, renderer);
    this->trees->render_floor(this->trees, renderer);
}

static void __create_lewt(Forest *this, struct SDL_Renderer *renderer)
{
#define FOREST_SIZE

    int i, rand_index, rand_x, rand_y, lower_x, lower_y, upper_x, upper_y;
    this->forest_lewt = CREATE_BAG();
    this->forest_lewt->items = malloc(sizeof(char *) * this->num_chests);
    this->lewt_cords_x = malloc(sizeof(int) * this->num_chests);
    this->lewt_cords_y = malloc(sizeof(int) * this->num_chests);
    this->treasure = malloc(sizeof(Collidable *) * this->num_chests);

    rand_index = 0;
    rand_x = 0;
    rand_y = 0;

    upper_x = this->forest_map_width - (WINDOW_WIDTH / 2);
    lower_x = this->forest_map_width + (WINDOW_WIDTH / 2);
    upper_y = this->forest_map_height - (WINDOW_HEIGHT / 2);
    lower_y = this->forest_map_height + (WINDOW_HEIGHT / 2);

    for (i = 0; i < this->num_chests; i++)
    {
        rand_x = (i + 50) * i;
        rand_y =  (i + 50) *i;
        this->lewt_cords_x[i] = rand_x;
        this->lewt_cords_y[i] = rand_y;
        rand_index = rand() % ITEM_QUANTITY;
        this->forest_lewt->items[i] = malloc(strlen(ITEMS[rand_index]) + 1);
        strcpy(this->forest_lewt->items[i], ITEMS[rand_index]);
        this->treasure[i] = CREATE_COLLIDABLE();
        this->treasure[i]->make_chest(this->treasure[i], renderer, rand_x, rand_y, 16, 16);
        printf("\nAdding %s to forest lewt collection.", this->forest_lewt->items[i]);
    }
}
Forest *CREATE_FOREST(int num_chests)
{
    Forest *this = (Forest *)malloc(sizeof(*this));

    this->create_assets = __create_assets;
    this->render_forest = __render_forest;
    this->create_lewt = __create_lewt;
    this->render_lewt = __render_lewt;
    this->forest_lewt = NULL;
    this->treasure = NULL;
    this->num_chests = num_chests;
    this->lewt_cords_x = NULL;
    this->lewt_cords_y = NULL;
    this->forest_map_width = 2048;
    this->forest_map_height = 1792;
    this->destroy = __destroy;

    return this;
}
