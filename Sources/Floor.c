
#include "Floor.h"
static void __destroy(Floor *obj)
{
    SDL_DestroyTexture(obj->texture);
    if (NULL != obj)
    {
        free(obj);
        obj = NULL;
    }
}

static void __set_texture(Floor *obj, struct SDL_Renderer *renderer, char *path)
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
    SDL_QueryTexture(texture, NULL, NULL, &MAP_WIDTH, &MAP_HEIGHT);
    obj->texture = texture;
}

static SDL_Rect *__get_rect_pointer(Floor *obj)
{
    return &obj->rect;
}

static void __render_floor(Floor *obj, struct SDL_Renderer *renderer)
{
    if (!MOVEMENT_DISABLED)
    {
        obj->rect.x = X;
        obj->rect.y = Y;
    }
    SDL_RenderCopy(renderer, obj->texture, obj->get_rect_pointer(obj), NULL);
}

Floor *create_floor(int x, int y, int w, int h)
{
    Floor *obj = (Floor *)malloc(sizeof(*obj));
    obj->set_texture = __set_texture;
    obj->destroy = __destroy;
    obj->get_rect_pointer = __get_rect_pointer;
    obj->render_floor = __render_floor;
    obj->rect.x = x;
    obj->rect.y = y;
    obj->rect.w = w;
    obj->rect.h = h;

    return obj;
}
