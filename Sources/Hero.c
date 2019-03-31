
#include "Hero.h"

int get_middle(int frame_size, int sprite_size)
{
    return (frame_size / 2) - (sprite_size / 2);
}

int time_to_animate()
{
    if (FRAMES_RENDERED % 10 == 0)
    {
        return 1;
    }
    return 0;
}

static void __destroy(Hero *obj)
{
    SDL_DestroyTexture(obj->texture);
    if (NULL != obj)
    {
        free(obj);
        obj = NULL;
    }
}

static void __set_texture(Hero *obj, struct SDL_Renderer *renderer, char *path)
{
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
    int width, height;

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
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    obj->rect.x = 0;
    obj->rect.y = 0;
    obj->rect.w = SPRITE_FRAME_WIDTH;
    obj->rect.h = SPRITE_FRAME_HEIGHT;
    obj->rect_pos.x = get_middle(WINDOW_WIDTH, SPRITE_FRAME_WIDTH);
    obj->rect_pos.y = get_middle(WINDOW_HEIGHT, SPRITE_FRAME_HEIGHT);
    obj->rect_pos.w = SPRITE_FRAME_WIDTH;
    obj->rect_pos.h = SPRITE_FRAME_HEIGHT;

    obj->texture = texture;
}

static SDL_Rect *__get_rect_pointer(Hero *obj)
{
    return &obj->rect;
}

static SDL_Rect *__get_rect_pos_pointer(Hero *obj)
{
    return &obj->rect_pos;
}

static void __render(Hero *obj, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, obj->texture, obj->get_rect_pointer(obj), obj->get_rect_pos_pointer(obj));
}

static void __animate_down(Hero *obj)
{
    obj->rect.y = 0;
    obj->rect.x += obj->rect.w;

    if (obj->rect.x >= obj->rect.w * 4)
    {
        obj->rect.x = 0;
    }
}

static void __animate_up(Hero *obj)
{
    obj->rect.y = obj->rect.h;
    obj->rect.x += obj->rect.w;

    if (obj->rect.x >= obj->rect.w * 4)
    {
        obj->rect.x = 0;
    }
}

static void __animate_left(Hero *obj)
{
    obj->rect.y = obj->rect.h * 2;
    obj->rect.x += obj->rect.w;

    if (obj->rect.x >= obj->rect.w * 4)
    {
        obj->rect.x = 0;
    }
}

static void __animate_right(Hero *obj)
{
    obj->rect.y = obj->rect.h * 3;
    obj->rect.x += obj->rect.w;

    if (obj->rect.x >= obj->rect.w * 4)
    {
        obj->rect.x = 0;
    }
}

static void __check_direction(Hero *obj)
{
    if (USER_INPUTS[0])
    {
        obj->animate_down(obj);
        FACING = DOWN;
    }
    else if (USER_INPUTS[1])
    {
        obj->animate_up(obj);
        FACING = UP;
    }
    else if (USER_INPUTS[2])
    {
        obj->animate_left(obj);
        FACING = LEFT;
    }
    else if (USER_INPUTS[3])
    {
        obj->animate_right(obj);
        FACING = RIGHT;
    }
}

static void __animate(Hero *obj)
{
    if (time_to_animate() && !MOVEMENT_DISABLED)
    {
        obj->check_direction(obj);
    }
}

Hero *CREATE_HERO()
{
    Hero *obj = (Hero *)malloc(sizeof(*obj));
    obj->set_texture = __set_texture;
    obj->destroy = __destroy;
    obj->render = __render;
    obj->get_rect_pointer = __get_rect_pointer;
    obj->get_rect_pos_pointer = __get_rect_pos_pointer;

    obj->animate = __animate;
    obj->check_direction = __check_direction;

    obj->animate_down = __animate_down;
    obj->animate_up = __animate_up;
    obj->animate_left = __animate_left;
    obj->animate_right = __animate_right;
    return obj;
}
