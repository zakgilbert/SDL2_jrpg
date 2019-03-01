#include "Collidable.h"
static void _destroy(Collidable *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static struct
    SDL_Texture *
    _create_collidable_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect * rect)
{
    struct SDL_Texture *texture = NULL;
    struct SDL_Surface *surface = NULL;

    surface = IMG_Load(path);

    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    return texture;
}
static struct SDL_Rect *_make_chest(Collidable *this, struct SDL_Renderer *renderer, int x, int y, int w, int h)
{
    this->first_texture = this->create_collidable_texture(renderer, "graphics/chestClose.png", &this->rect_1);
    this->second_texture = this->create_collidable_texture(renderer, "graphics/chestOpen.png", &this->rect_2);
    this->rect_1.x = 150;
    this->rect_1.y = 150;
    this->rect_1.w = w;
    this->rect_1.h = h;
    this->x = x;
    this->y = y;
    return &this->rect_1;
}

Collidable *CREATE_COLLIDABLE()
{
    Collidable *this = (Collidable *)malloc(sizeof(*this));
    this->destroy = _destroy;
    this->create_collidable_texture = _create_collidable_texture;
    this->make_chest = _make_chest;
    this->first_texture = NULL;
    this->second_texture = NULL;

    this->x = 0;
    this->y = 0;

    return this;
}