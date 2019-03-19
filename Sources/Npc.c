#include "Npc.h"

static void _destroy(Npc *this)
{
    SDL_DestroyTexture(this->texture);

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _render(Npc *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
    SDL_RenderDrawRect(renderer, &this->rect);
}

Npc *CREATE_NPC(struct SDL_Renderer *renderer, int x, int y, int index, int key, char *path)
{
    Npc *this = (Npc *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->render = _render;

    this->index = index;
    this->rect.x = x;
    this->rect.y = y;
    this->key = key;
    this->x = x;
    this->y = y;
    this->texture = create_texture(renderer, path, &this->rect);

    return this;
}