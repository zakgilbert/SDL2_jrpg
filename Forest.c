//
// Created by zachary on 1/23/19.
//

#include "Forest.h"

static void __destroy (Forest *forest)
{
    forest->floor->destroy(forest->floor);
    forest->trees->destroy(forest->trees);

    if (NULL != forest) {
        free(forest);
        forest = NULL;
    }
}

static void __create_assets (Forest *forest, struct SDL_Renderer *renderer)
{
    forest->floor = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    forest->trees = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    forest->floor->set_texture(forest->floor, renderer, "graphics/map.png");
    forest->trees->set_texture(forest->trees, renderer, "graphics/forest.png");
}

static void __render_forest (Forest *forest, struct SDL_Renderer *renderer, Hero *hero)
{
    if (INPUT == CANCEL) {
        state = MAIN_MENU;
        previous_state = DARK_FOREST;
        INPUT = NONE;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        return;
    }
    MOVEMENT_DISABLED = 0;
    hero->animate(hero);
    forest->floor->render_floor(forest->floor, renderer);
    hero->render(hero, renderer);
    forest->trees->render_floor(forest->trees, renderer);
}

Forest *CREATE_FOREST ()
{
    Forest *forest = (Forest *) malloc(sizeof(*forest));

    forest->create_assets = __create_assets;
    forest->render_forest = __render_forest;
    forest->destroy = __destroy;

    return forest;

}
