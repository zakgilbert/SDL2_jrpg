//
// Created by zachary on 1/24/19.
//

#include "Menu.h"

struct SDL_Color white = {255, 255, 255};
struct SDL_Color grey = {123, 45, 87};
uint32_t transition_delay = 200;

static void __destroy(Menu *obj)
{
    obj->main_menu_bg->destroy(obj->main_menu_bg);
    if (NULL != obj)
    {
        free(obj);
        obj = NULL;
    }
}

static void __render_items_menu(Menu *obj, struct SDL_Renderer *renderer, Hand *hand)
{
    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        INPUT = NONE;
        hand->main_menu_position(hand);
        hand->current_state = 0;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &obj->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
        return;
    }
    MOVEMENT_DISABLED = 1;
    hand->change_state_quantity(hand, 3, 0);
    obj->main_menu_bg->render(obj->main_menu_bg, renderer);
    hand->move_vertical(hand, obj->render_items_menu_options(obj, renderer, hand->current_state));
    hand->render(hand, renderer);
}

static int __render_items_menu_options(Menu *obj, struct SDL_Renderer *renderer, int current_state)
{
    int skip;
    char font_path[] = "ponde___.ttf";

    obj->font = TTF_OpenFont(font_path, 10);

    if (!obj->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(obj->font);
    obj->rect.x = 40;
    obj->rect.y = 15;

    for (int i = 0; i < 4; i++)
    {
        TTF_SizeText(obj->font, ITEMS[i], &obj->rect.w, &obj->rect.h);

        if (i == current_state)
        {
            obj->surface = TTF_RenderText_Solid(obj->font, ITEMS[i], white);
        }
        else
        {
            obj->surface = TTF_RenderText_Solid(obj->font, ITEMS[i], grey);
        }
        obj->texture = SDL_CreateTextureFromSurface(renderer, obj->surface);
        SDL_RenderCopy(renderer, obj->texture, NULL, &obj->rect);

        obj->rect.y += skip;
    }
    TTF_CloseFont(obj->font);
    SDL_FreeSurface(obj->surface);
    SDL_DestroyTexture(obj->texture);
    obj->surface = NULL;
    obj->texture = NULL;
    return skip;
}

static int __render_main_menu_options(Menu *obj, struct SDL_Renderer *renderer, int current_state)
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
    obj->font = TTF_OpenFont(font_path, 12);

    if (!obj->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(obj->font) + 6;
    obj->rect.x = 270;
    obj->rect.y = 15;
    for (int i = 0; i < 7; i++)
    {
        TTF_SizeText(obj->font, main_menu_options[i], &obj->rect.w, &obj->rect.h);

        if (i == current_state)
        {
            obj->surface = TTF_RenderText_Solid(obj->font, main_menu_options[i], white);
        }
        else
        {
            obj->surface = TTF_RenderText_Solid(obj->font, main_menu_options[i], grey);
        }
        obj->texture = SDL_CreateTextureFromSurface(renderer, obj->surface);
        SDL_RenderCopy(renderer, obj->texture, NULL, &obj->rect);

        obj->rect.y += skip;
    }
    TTF_CloseFont(obj->font);
    SDL_FreeSurface(obj->surface);
    SDL_DestroyTexture(obj->texture);
    obj->surface = NULL;
    obj->texture = NULL;
    return skip;
}

static void __render_main_menu(Menu *obj, struct SDL_Renderer *renderer, Hand *hand)
{
    if (INPUT == CANCEL)
    {
        state = previous_state;
        INPUT = NONE;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &obj->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
        return;
    }
    hand->change_state_quantity(hand, obj->option_states, 0);
    MOVEMENT_DISABLED = 1;
    obj->main_menu_bg->render(obj->main_menu_bg, renderer);
    hand->move_vertical(hand, obj->render_main_menu_options(obj, renderer, hand->current_state));
    hand->render(hand, renderer);

    if (hand -> current_state == 0 && inputs[4])
    {
        state = ITEMS_MENU;
        hand->items_menu_position(hand);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &obj->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
    }
}

Menu *CREATE_MENU()
{
    Menu *obj = (Menu *)malloc(sizeof(*obj));
    // -n>
    obj->destroy = __destroy;
    obj->render_main_menu = __render_main_menu;
    obj->render_main_menu_options = __render_main_menu_options;
    obj->render_items_menu = __render_items_menu;
    obj->render_items_menu_options = __render_items_menu_options;
    // -o>
    obj->main_menu_bg = CREATE_WINDOW(12, 8, 336, 306);
    obj->font = NULL;
    obj->surface = NULL;
    obj->texture = NULL;
    obj->option_states = 6;
    obj->transition.x = 0;
    obj->transition.y = 0;
    obj->transition.w = WINDOW_WIDTH;
    obj->transition.h = WINDOW_HEIGHT;

    return obj;
}