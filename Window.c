//
// Created by zachary on 1/24/19.
//

#include "Window.h"

static void __create_borders (Window *obj, int padding, struct SDL_Rect * border)
{
    border -> x = (obj->rect.x - padding);
    border -> y = (obj->rect.y - padding);
    border -> w = (obj->rect.w);
    border -> h = (obj->rect.h);
}

static void __destroy (Window *obj)
{
    if (NULL != obj) {
        free(obj);
        obj = NULL;
    }
}

static void __render (Window *obj, struct SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor( renderer, 52, 104, 188, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect( renderer, &obj->rect);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect( renderer, &obj->border_1);
    SDL_RenderDrawRect( renderer, &obj->border_2);
    SDL_RenderDrawRect( renderer, &obj->border_3);
    SDL_RenderDrawRect( renderer, &obj->border_4);
}

Window *CREATE_WINDOW (int x, int y, int w, int h)
{
    Window *obj = (Window *) malloc(sizeof(*obj));
    obj->destroy = __destroy;
    obj->render = __render;
    obj->create_borders = __create_borders;
    obj->rect.x = x;
    obj->rect.y = y;
    obj->rect.w = w;
    obj->rect.h = h;
    obj->create_borders(obj, 0, &obj->border_1);
    obj->create_borders(obj, 1, &obj->border_2);
    obj->create_borders(obj, 2, &obj->border_3);
    obj->create_borders(obj, 3, &obj->border_4);
    return obj;
}