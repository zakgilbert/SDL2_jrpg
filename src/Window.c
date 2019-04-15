
#include "Window.h"

static void _create_borders(Window *this, int padding, struct SDL_Rect *border)
{
    border->x = (this->rect.x - padding);
    border->y = (this->rect.y - padding);
    border->w = (this->rect.w);
    border->h = (this->rect.h);
}

static void _destroy(Window *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static int _timer_is_maxed(Window *this)
{
    return this->rect.w >= this->original_width;
}
static int _adjust_menu_colors(Window *this)
{
    if (LEFT())
    {
        this->color_value--;
    }
    else if (RIGHT())
    {
        this->color_value++;
    }
    if (this->color_value >= 254)
    {
        this->color_value = 254;
    }
    else if (this->color_value <= 1)
    {
        this->color_value = 1;
    }
    return this->color_value;
}
static void _render_color_bar(Window *this, struct SDL_Renderer *renderer)
{
    struct SDL_Rect color_bar;
    color_bar.x = this->rect.x;
    color_bar.y = this->rect.y;
    color_bar.h = this->rect.h;

    color_bar.w = (this->rect.w * (this->color_value)) / 255;

    SDL_SetRenderDrawColor(renderer, this->color_bar_color.r, this->color_bar_color.g, this->color_bar_color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &color_bar);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->border_1);
    SDL_RenderDrawRect(renderer, &this->border_2);
    SDL_RenderDrawRect(renderer, &this->border_3);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
static void _render_time_bar(Window *this, struct SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->border_1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
static void _render(Window *this, struct SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, MENU_BACKGROUND.r, MENU_BACKGROUND.g, MENU_BACKGROUND.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->border_1);
    SDL_RenderDrawRect(renderer, &this->border_2);
    SDL_RenderDrawRect(renderer, &this->border_3);
    SDL_RenderDrawRect(renderer, &this->border_4);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

Window *CREATE_WINDOW(int x, int y, int w, int h)
{
    Window *this = (Window *)malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->create_borders = _create_borders;
    this->render_color_bar = _render_color_bar;
    this->adjust_menu_colors = _adjust_menu_colors;
    this->render_time_bar = _render_time_bar;
    this->timer_is_maxed = _timer_is_maxed;

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
    this->original_width = w;
    this->color_value = 0;
    this->seconds_passed = 0;
    this->now = GAME_SECS;
    this->create_borders(this, 0, &this->border_1);
    this->create_borders(this, 1, &this->border_2);
    this->create_borders(this, 2, &this->border_3);
    this->create_borders(this, 3, &this->border_4);
    return this;
}
Window *BATTLE_PRIMARY()
{
    return CREATE_WINDOW(192, 230, 85, WINDOW_HEIGHT - 245);
}
Window *BATTLE_MAGIC()
{
    return CREATE_WINDOW(200, 220, 85, WINDOW_HEIGHT - 245);
}
void render_window(void *obj, struct SDL_Renderer *renderer)
{
    Window *this = (Window *)obj;
    this->render(this, renderer);
}
void render_window_color_bar(void *obj, struct SDL_Renderer *renderer)
{
    Window *this = (Window *)obj;
    this->render_color_bar(this, renderer);
}