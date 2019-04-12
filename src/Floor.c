
#include "Floor.h"
static void _destroy(Floor *this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _set_texture(Floor *this, struct SDL_Renderer *renderer, char *path)
{
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
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
    SDL_QueryTexture(texture, NULL, NULL, &this->rect.w, &this->rect.h);
    this->texture = texture;
}

static void _render(Floor *this, struct SDL_Renderer *renderer)
{
    if (!MOVEMENT_DISABLED)
    {
        this->rect.x = X;
        this->rect.y = Y;
    }
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

Floor *create_floor(int x, int y, int w, int h)
{
    Floor *this = (Floor *)malloc(sizeof(*this));
    this->set_texture = _set_texture;
    this->destroy = _destroy;
    this->render = _render;
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;

    return this;
}

void render_floor(void *obj, struct SDL_Renderer *renderer)
{
    Floor *this = (Floor *)obj;
    this->render(this, renderer);
}