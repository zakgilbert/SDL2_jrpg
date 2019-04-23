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

static void _render_one_frame(Npc *this, struct SDL_Renderer *renderer)
{
    if (!MOVEMENT_DISABLED)
    {
        this->rect.x = this->x + X;
        this->rect.y = this->y + Y;
    }
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
    /**
        SDL_RenderDrawRect(renderer, &this->rect);
*/
}
static void _render_sprite(Npc *this, struct SDL_Renderer *renderer)
{
    if (!MOVEMENT_DISABLED)
    {
        this->rect.x = this->x + X;
        this->rect.y = this->y + Y;
    }
    SDL_RenderCopy(renderer, this->texture, &this->rect2, &this->rect);
    /**
    SDL_RenderDrawRect(renderer, &this->rect);
*/
}

static int _interact(Npc *this)
{
    if (this->ready_to_interact && CONFIRM())
    {
        return this->key;
    }
    return -1;
}

Npc *CREATE_NPC(struct SDL_Renderer *renderer, int x, int y, int index, int key, char *path, int type)
{
    Npc *this = (Npc *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->interact = _interact;

    this->ready_to_interact = 0;
    this->index = index;
    this->rect.x = x;
    this->rect.y = y;
    this->key = key;
    this->type = type;
    this->x = x;
    this->y = y;
    switch (this->type)
    {
    case SPRITE:
        this->texture = create_texture(renderer, path, &this->rect2);
        this->rect2.x = 0;
        this->rect2.y = 0;
        this->rect.w = SPRITE_FRAME_WIDTH;
        this->rect.h = SPRITE_FRAME_HEIGHT;
        this->rect2.w = SPRITE_FRAME_WIDTH;
        this->rect2.h = SPRITE_FRAME_HEIGHT;
        this->render = _render_sprite;
        break;
    case ONE_FRAME:
        this->texture = create_texture(renderer, path, &this->rect);
        this->render = _render_one_frame;
        break;
    default:
        break;
    }

    return this;
}
void render_npc(void *obj, struct SDL_Renderer *renderer)
{
    Npc *this = (Npc *)obj;
    this->render(this, renderer);
}