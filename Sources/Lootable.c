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
static void _loot(Lootable *this)
{
    this->texture = this->alt_tex;
    this->looted = 1;
}
Lootable *CREATE_LOOTABLE(struct SDL_Renderer *renderer, int index)
{
    Lootable *this = (Lootable *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->loot = _loot;

    this->texture = create_texture(renderer, "../graphics/chestClose.png", this->rect);
    this->alt_tex = create_texture(renderer, "../graphics/chestOpen.png", this->rect);
    this->looted = 0;
    this->index = index;

    return this;
}