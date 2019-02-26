//
// Created by zachary on 1/24/19.
//

#include "Menu.h"

struct SDL_Color white = {255, 255, 255};
struct SDL_Color grey = {123, 45, 87};
uint32_t transition_delay = 200;

static void __destroy(Menu *this)
{
    this->main_menu_bg->destroy(this->main_menu_bg);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void __render_items_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        INPUT = NONE;
        hand->main_menu_position(hand);
        hand->current_state = 0;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
        return;
    }
    MOVEMENT_DISABLED = 1;
    hand->change_state_quantity(hand, ITEMS_IN_BAG - 1, 0);
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    hand->move_vertical(hand, this->render_items_menu_options(this, renderer, hand->current_state));
    hand->render(hand, renderer);
}

static void __render_use_item_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand)
{
    if (INPUT == CANCEL)
    {
        state = ITEMS_MENU;
        INPUT = NONE;
        hand->items_menu_position(hand);
        hand->current_state = 0;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
        return;
    }
    MOVEMENT_DISABLED = 1;
}
static int render_use_item_menu_options(Menu *this, struct SDL_Renderer *renderer, int current_state)
{
}
static int __render_items_menu_options(Menu *this, struct SDL_Renderer *renderer, int current_state)
{
    int skip;
    char font_path[] = "ponde___.ttf";
    struct SDL_Surface *quat;
    struct SDL_Rect quat_rect;
    struct SDL_Texture *quat_tex;

    TTF_Font *quat_font;
    char quat_array[2];
    this->font = TTF_OpenFont(font_path, 10);
    quat_font = this->font;
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font);
    this->rect.x = 49;
    this->rect.y = 15;
    quat_rect.x = 200;
    quat_rect.y = 15;

    for (int i = 0; i < ITEMS_IN_BAG; i++)
    {
        TTF_SizeText(this->font, BAG[i], &this->rect.w, &this->rect.h);
        sprintf(quat_array, "%d", BAG_QUANTITIES[i]);
        TTF_SizeText(quat_font, quat_array, &quat_rect.w, &quat_rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, BAG[i], white);
            quat = TTF_RenderText_Solid(quat_font, quat_array, white);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, BAG[i], grey);
            quat = TTF_RenderText_Solid(quat_font, quat_array, grey);
        }
        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        quat_tex = SDL_CreateTextureFromSurface(renderer, quat);
        SDL_RenderCopy(renderer, quat_tex, NULL, &quat_rect);
        SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
        quat_rect.y += skip;
        this->rect.y += skip;
    }
    TTF_CloseFont(this->font);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(quat);
    SDL_DestroyTexture(quat_tex);
    this->surface = NULL;
    this->texture = NULL;
    return skip;
}

static int __render_main_menu_options(Menu *this, struct SDL_Renderer *renderer, int current_state)
{
    int skip;
    char font_path[] = "ponde___.ttf";
    const char main_menu_options[7][7] = {
        {"Items"},
        {"Skills"},
        {"Magic"},
        {"Status"},
        {"Config"},
        {"Save"},
        {"Exit"}};
    this->font = TTF_OpenFont(font_path, 12);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font) + 6;
    this->rect.x = 270;
    this->rect.y = 15;
    for (int i = 0; i < 7; i++)
    {
        TTF_SizeText(this->font, main_menu_options[i], &this->rect.w, &this->rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, main_menu_options[i], white);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, main_menu_options[i], grey);
        }
        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);

        this->rect.y += skip;
    }
    TTF_CloseFont(this->font);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    this->surface = NULL;
    this->texture = NULL;
    return skip;
}

static void __render_main_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand)
{
    if (INPUT == CANCEL)
    {
        state = previous_state;
        INPUT = NONE;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
        return;
    }
    hand->change_state_quantity(hand, this->option_states, 0);
    MOVEMENT_DISABLED = 1;
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    hand->move_vertical(hand, this->render_main_menu_options(this, renderer, hand->current_state));
    hand->render(hand, renderer);

    if (hand->current_state == 0 && inputs[4])
    {
        state = ITEMS_MENU;
        hand->items_menu_position(hand);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
    }
}

Menu *CREATE_MENU()
{
    Menu *this = (Menu *)malloc(sizeof(*this));
    // -n>
    this->destroy = __destroy;
    this->render_main_menu = __render_main_menu;
    this->render_main_menu_options = __render_main_menu_options;
    this->render_items_menu = __render_items_menu;
    this->render_items_menu_options = __render_items_menu_options;
    // -o>
    this->main_menu_bg = CREATE_WINDOW(12, 8, 336, 306);
    this->select_character_bg = CREATE_WINDOW(12, 200, 336, 153);
    this->font = NULL;
    this->surface = NULL;
    this->texture = NULL;
    this->option_states = 6;
    this->transition.x = 0;
    this->transition.y = 0;
    this->transition.w = WINDOW_WIDTH;
    this->transition.h = WINDOW_HEIGHT;

    return this;
}