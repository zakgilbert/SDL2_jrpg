
#include "Graphics.h"

struct
    SDL_Texture *
    create_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect *rect)
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