
/************************
 *  Enemy.c
*/

#include "Enemy.h"

static void _destroy(Enemy *this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _render(Enemy *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}
Enemy *CREATE_ENEMY(int key, struct SDL_Renderer *renderer)
{
    Enemy *this = malloc(sizeof(*this));
    this->key = key;
    this->destroy = _destroy;
    this->render = _render;
    this->type = MONSTER;

    this->texture = create_texture(renderer, ENEMY_PATHS->list[key], &this->rect);
    return this;
}
