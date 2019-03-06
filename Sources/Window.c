//
// Created by zachary on 1/24/19.
//

#include "Window.h"

static void __create_borders(Window *this, int padding, struct SDL_Rect *border)
{
    border->x = (this->rect.x - padding);
    border->y = (this->rect.y - padding);
    border->w = (this->rect.w);
    border->h = (this->rect.h);
}

static void __destroy(Window *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static int __adjust_menu_colors(Window *this)
{
    if(inputs[2])
    {
        this->color_value--;
    }
    else if(inputs[3])
    {
        this->color_value++;
    }
    if (this-> color_value >= 254)
    {
        this-> color_value = 254;
    }
    else if (this -> color_value <= 1)
    {
        this -> color_value = 1;
    }
    return this->color_value;
}
static void __render_color_bar(Window **this, struct SDL_Renderer *renderer, int x, int y, int skip, int i)
{
    struct SDL_Rect color_bar;
    color_bar.x = this[i] -> rect.x;
    color_bar.y = this[i] -> rect.y;
    color_bar.h = this[i] -> rect.h;

    color_bar.w = (this[i] -> rect.w *(this[i] -> color_value)) / 255;

    SDL_SetRenderDrawColor(renderer, this[i]->color_bar_color.r,this[i]->color_bar_color.g, this[i]->color_bar_color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &color_bar);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this[i] -> border_1);
    SDL_RenderDrawRect(renderer, &this[i] -> border_2);
    SDL_RenderDrawRect(renderer, &this[i] -> border_3);
}
static void __render(Window *this, struct SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, MENU_BACKGROUND.r, MENU_BACKGROUND.g, MENU_BACKGROUND.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->border_1);
    SDL_RenderDrawRect(renderer, &this->border_2);
    SDL_RenderDrawRect(renderer, &this->border_3);
    SDL_RenderDrawRect(renderer, &this->border_4);
}

Window *CREATE_WINDOW(int x, int y, int w, int h)
{
    Window *this = (Window *)malloc(sizeof(*this));
    this->destroy = __destroy;
    this->render = __render;
    this->create_borders = __create_borders;
    this->render_color_bar = __render_color_bar;
    this->adjust_menu_colors = __adjust_menu_colors;
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
    this->color_value = 0;
    this->create_borders(this, 0, &this->border_1);
    this->create_borders(this, 1, &this->border_2);
    this->create_borders(this, 2, &this->border_3);
    this->create_borders(this, 3, &this->border_4);
    return this;
}