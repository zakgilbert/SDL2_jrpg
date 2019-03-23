
/************************
 *  Battle.c
*/

#include "Battle.h"
static void _destroy(Battle *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _create_battle_textures(Battle *this, struct SDL_Renderer *renderer)
{
    this->textures = malloc(sizeof(struct SDL_Texture *) * BATTLE_LINEUP[this->area]->num_ints[this->roll]);
    for (size_t i = 0; i < this->num_enemies; i++)
    {
        this->textures[i] = create_texture(renderer, ENEMY_PATHS->list[BATTLE_LINEUP[this->area]->list[this->roll][i]], &this->rect);
    }
    this->back_ground->set_texture(this->back_ground, renderer, BATTLE_BACKGROUNDS->list[this->area]);
    
}
static void _render(Battle *this, struct SDL_Renderer *renderer)
{
    this->back_ground->render_floor(this->back_ground, renderer);
    for (size_t i = 0; i < this->num_enemies; i++)
    {
        SDL_RenderCopy(renderer, this->textures[i], NULL, &this->rect);
    }
}

Battle *CREATE_BATTLE(int area, int roll, struct SDL_Renderer *renderer)
{
    Battle *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->create_battle_textures = _create_battle_textures;
    this->back_ground = create_floor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    this->roll = roll;
    this->area = area;
    this->rect.x = 50;
    this->rect.y = WINDOW_HEIGHT / 2;
    this->num_enemies = BATTLE_LINEUP[this->area]->num_ints[this->roll];
    this->create_battle_textures(this, renderer);
    return this;
}