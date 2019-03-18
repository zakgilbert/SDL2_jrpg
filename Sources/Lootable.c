#include "Lootable.h"

static void _destroy(Lootable *this)
{
    SDL_DestroyTexture(this->texture);
    SDL_DestroyTexture(this->alt_tex);

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _render(Lootable *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, this->rect);
}

static void _loot(Lootable *this)
{
    if (!this->looted)
    {
        this->texture = this->alt_tex;
        this->looted = 1;
    }
}

Lootable *CREATE_LOOTABLE(struct SDL_Renderer *renderer, int x, int y, int index, int key)
{
    Lootable *this = (Lootable *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->loot = _loot;
    this->render = _render;

    this->looted = 0;
    this->index = index;
    this->rect->x = x;
    this->rect->y = y;
    this->key = key;
    this->x = x;
    this->y = y;

    return this;
}