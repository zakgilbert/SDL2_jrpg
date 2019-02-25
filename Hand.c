//
// Created by zachary on 1/27/19.
//

#include "Hand.h"

static void __destroy (Hand *obj)
{
    SDL_DestroyTexture(obj->texture);
    if (NULL != obj) {
        free(obj);
        obj = NULL;
    }
}

static void __items_menu_position(Hand * obj)
{
    obj->position.x = 15;
    obj->position.y = 11;
}
static void __main_menu_position(Hand * obj)
{
    obj->position.x = 233;
    obj->position.y = 11;
}

static void __render (Hand *obj, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, obj->texture, obj->get_rect_pointer(obj), obj->get_rect_pos_pointer(obj));
}

static void __create_texture (Hand *obj, char *path, struct SDL_Renderer *renderer, int x, int y)
{
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
    int width, height;

    surface = IMG_Load(path);
    if (!surface) {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    obj->rect.x = 0;
    obj->rect.y = 0;
    obj->rect.w = 32;
    obj->rect.h = 32;
    obj->position.x = x;
    obj->position.y = y;
    obj->position.w = 32;
    obj->position.h = 32;

    obj->texture = texture;
}

static SDL_Rect *__get_rect_pos_pointer (Hand *obj)
{
    return &obj->position;
}

static SDL_Rect *__get_rect_pointer (Hand *obj)
{
    return &obj->rect;
}

int __change_state_quantity (Hand *obj, int number, int add)
{
    if (add) {
        obj->number_of_states += number;
    } else {
        obj->number_of_states = number;
    }
    return obj->number_of_states;
}

int __change_get_state (Hand *obj, int number, int add)
{
    if (add) {
        obj->current_state += number;
    } else {
        obj->current_state = number;
    }
    return obj->current_state;
}

static void __animate (Hand *obj)
{
    if (FRAMES_RENDERED % 10 == 0 ) {
        obj->rect.x += obj->rect.w;

        if ((obj->rect.x >= obj->rect.w * 4) && (obj->rect.y == 0)) {
            obj->rect.x = 0;
            obj->rect.y = obj->rect.h;
        } else if ((obj->rect.x >= obj->rect.w * 4) && (obj->rect.y == obj->rect.h)) {
            obj->rect.y = 0;
            obj->rect.x = 0;
        }
    }
}

static int __move_horizontal (Hand *obj, int distance)
{
    if (inputs[2] && obj->current_state > 0) {
        obj->position.x -= distance;
        obj->current_state--;
    } else if (inputs[3] && obj->current_state < obj->number_of_states) {
        obj->position.x += distance;
        obj->current_state++;
    }
    return obj->current_state;
}

static int __move_vertical (Hand *obj, int distance)
{
    if (inputs[1] && obj->current_state > 0) {
        obj->position.y -= distance;
        obj->current_state--;
        refresh_inputs(inputs, 6);
    } else if (inputs[0] && obj->current_state < obj->number_of_states) {
        obj->position.y += distance;
        obj->current_state++;
        refresh_inputs(inputs, 6);
    }
    return obj->current_state;
}

Hand *CREATE_HAND ()
{
    Hand *obj = (Hand *) malloc(sizeof(*obj));

    // -n>
    obj->destroy                =    __destroy;
    obj->render                 =    __render;
    obj->create_texture         =    __create_texture;
    obj->animate                =    __animate;

    obj->change_state_quantity  =    __change_state_quantity;
    obj->change_get_state       =    __change_get_state;

    obj->get_rect_pos_pointer   =    __get_rect_pos_pointer;
    obj->get_rect_pointer       =    __get_rect_pointer;

    obj->move_vertical          =    __move_vertical;
    obj->move_horizontal        =    __move_horizontal;
    obj->items_menu_position    =    __items_menu_position;
    obj->main_menu_position     =    __main_menu_position;
    // -o>
    obj->current_state = 0;
    return obj;
}
