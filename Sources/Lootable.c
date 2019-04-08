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

static Lootable *_render(Lootable *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
    SDL_RenderDrawRect(renderer, &this->rect);
    return this;
}

static int _loot(Lootable *this)
{
    if (!this->looted && USER_INPUTS[4])
    {
        this->texture = this->alt_tex;
        this->looted = 1;
        return this->key;
    }
    return -1;
}

Lootable *CREATE_LOOTABLE(struct SDL_Renderer *renderer, int x, int y, int index, int key)
{
    Lootable *this = (Lootable *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->loot = _loot;
    this->render = _render;

    this->looted = 0;
    this->ready_to_interact = 0;
    this->index = index;
    this->rect.x = x;
    this->rect.y = y;
    this->key = key;
    this->x = x;
    this->y = y;
    this->texture = create_texture(renderer, "graphics/chestClose.png", &this->rect);
    this->alt_tex = create_texture(renderer, "graphics/chestOpen.png", &this->rect);

    return this;
}

void render_lootable(void *obj, struct SDL_Renderer *renderer)
{
    Lootable *this = (Lootable *)obj;
    this->render(this, renderer);
}