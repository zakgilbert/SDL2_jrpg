
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
}
static void _render(Battle *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->back_ground, NULL, &this->bg_rect);
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
    this->bg_rect.x = 0;
    this->bg_rect.y = 0;

    this->back_ground = create_texture(renderer, BATTLE_BACKGROUNDS->list[area], &this->bg_rect);

    this->roll = roll;
    this->area = area;
    this->rect.x = 50;
    this->rect.y = WINDOW_HEIGHT / 2;
    this->num_enemies = BATTLE_LINEUP[this->area]->num_ints[this->roll];
    this->create_battle_textures(this, renderer);
    return this;
}