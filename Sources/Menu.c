//
// Created by zachary on 1/24/19.
//

#include "Menu.h"

uint32_t transition_delay = 200;

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static const char *MENU_OPTIONS[] = {
    FOREACH_MENU_OPTION(GENERATE_STRING)};
/**
 * Destructor for the Menu "class"
 * 
 * @args:    Menu * this
 * @returns: void
 */
static void _destroy(Menu *this)
{
    this->main_menu_bg->destroy(this->main_menu_bg);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _render_main_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand, Character **characters)
{
    if (INPUT == CANCEL)
    {
        state = previous_state;
        previous_state = MAIN_MENU;
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

    this->render_character_main_menu_image(this, renderer, hand, characters);
    this->render_character_stats(this, renderer, hand, 80, 15, 9, MAIN_MENU);

    if (hand->current_state == Items && USER_INPUTS[4])
    {
        state = ITEMS_MENU;
        hand->items_menu_position(hand);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
    }
    else if (hand->current_state == Config && USER_INPUTS[4])
    {
        state = CONFIG;
        hand->config_menu_position(hand);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
    }
    else if (hand->current_state == Save && USER_INPUTS[4])
    {
        state = SAVE;
        hand->save_menu_position(hand);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay);
    }
    else if (hand->current_state == Exit && USER_INPUTS[4])
    {
        INPUT = QUIT;
    }
}

static int _render_main_menu_options(Menu *this, struct SDL_Renderer *renderer, int current_state)
{
    int skip;
    char font_path[] = "ponde___.ttf";
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
        TTF_SizeText(this->font, MENU_OPTIONS[i], &this->rect.w, &this->rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, MENU_OPTIONS[i], WHITE);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, MENU_OPTIONS[i], GREY);
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

static void _render_character_stats(Menu *this, struct SDL_Renderer *renderer, Hand *hand, int x, int y, int font_size, int cas)
{
    int skip;
    char font_path[] = "ponde___.ttf";
    size_t len = NUM_CHARACTERS * 4;
    int j = 0;

    this->font = TTF_OpenFont(font_path, font_size);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font);
    this->rect.x = x;
    this->rect.y = y;
    switch (cas)
    {
    case MAIN_MENU:
        for (size_t i = 0; i < len; i++)
        {
            TTF_SizeText(this->font, STAT_MATRIX[i], &this->rect.w, &this->rect.h);
            this->surface = TTF_RenderText_Solid(this->font, STAT_MATRIX[i], WHITE);
            this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
            SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
            if ((i + 1) % 4 == 0 && i != 0)
            {
                this->rect.y += 50;
            }
            else
            {
                this->rect.y += skip;
            }
        }
        break;

    case USE_ITEM:

        for (size_t i = 0; i < NUM_CHARACTERS; i++)
        {
            if (i == 2)
            {
                this->rect.x = x;
                this->rect.y = y + 50;
            }
            else if (i == 3)
            {
                this->rect.y = y + 50;
            }

            for (; j < NUM_STATS + (i * NUM_STATS); j++)
            {
                TTF_SizeText(this->font, STAT_MATRIX[j], &this->rect.w, &this->rect.h);
                if (i == hand->current_state)
                {
                    this->surface = TTF_RenderText_Solid(this->font, STAT_MATRIX[j], WHITE);
                }
                else
                {
                    this->surface = TTF_RenderText_Solid(this->font, STAT_MATRIX[j], GREY);
                }
                this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
                SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
                this->rect.y += skip;
            }

            this->rect.x += 165;
            this->rect.y = y;
        }
        break;
    default:
        break;
    }
    TTF_CloseFont(this->font);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    this->surface = NULL;
    this->texture = NULL;
}

static void _render_character_main_menu_image(Menu *this, struct SDL_Renderer *renderer, Hand *hand, Character **characters)
{
    int i, j;

    j = 15;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        characters[i]->character_rect.x = 20;
        characters[i]->character_rect.w = 45;
        characters[i]->character_rect.h = 45;
        characters[i]->character_rect.y = j;
        SDL_RenderCopy(renderer, characters[i]->character_texture, NULL, &characters[i]->character_rect);
        j += 80;
    }
}

static void _render_items_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand, Item *bag)
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
    hand->change_state_quantity(hand, bag->items_in_bag - 1, 0);
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    hand->move_vertical(hand, this->render_items_menu_options(this, renderer, bag, hand->current_state));

    if (USER_INPUTS[4])
    {
        state = USE_ITEM;
        hand->use_item_position(hand);
        SDL_Delay(transition_delay);
        this->item_being_used = hand->current_state;
        hand->current_state = 0;
        this->previous_number_of_states = hand->number_of_states;
    }
}

static int _render_items_menu_options(Menu *this, struct SDL_Renderer *renderer, Item *bag, int current_state)
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
    for (int i = 0; i < bag->items_in_bag; i++)
    {
        TTF_SizeText(this->font, ITEMS[bag->items[i]], &this->rect.w, &this->rect.h);
        sprintf(quat_array, "%d", bag->item_quantities[i]);
        TTF_SizeText(quat_font, quat_array, &quat_rect.w, &quat_rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, ITEMS[bag->items[i]], WHITE);
            quat = TTF_RenderText_Solid(quat_font, quat_array, WHITE);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, ITEMS[bag->items[i]], GREY);
            quat = TTF_RenderText_Solid(quat_font, quat_array, GREY);
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

static void _render_use_item_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand, Character **party, Item *bag)
{
    if (INPUT == CANCEL)
    {
        state = ITEMS_MENU;
        INPUT = NONE;
        hand->current_state = this->item_being_used;
        hand->items_menu_position(hand);
        hand->number_of_states = this->previous_number_of_states;
        return;
    }
    MOVEMENT_DISABLED = 1;
    hand->change_state_quantity(hand, NUM_CHARACTERS - 1, 0);
    // printf ("\nState Q: %d", hand->number_of_states);
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    this->render_items_menu_options(this, renderer, bag, this->item_being_used);
    this->select_character_bg->render(this->select_character_bg, renderer);
    hand->vertical_horizontal(hand);
    //printf("\nCurrent_State: %d", hand->current_state);
    //  this->render_use_item_menu_options(this, renderer, party, hand->current_state);
    this->render_character_stats(this, renderer, hand, 49, 205, 9, USE_ITEM);
    hand->render(hand, renderer);
    if (USER_INPUTS[4])
    {
        int was_item_removed = bag->quaff_item(bag, CREATE_AFFECT(bag->items[this->item_being_used], party[hand->current_state]));

        this->previous_number_of_states += was_item_removed;
        if (was_item_removed == -1)
        {
            INPUT = CANCEL;
            SDL_Delay(300);
        }
    }
}
static void _render_config_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand)
{
    /*******************************************************
     * If Cancel button is pressed. Return to the main menu.
  */
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
    /************************************
     * Otherwise, render the config menu.
  */
    MOVEMENT_DISABLED = 1;
    hand->change_state_quantity(hand, 2, 0);
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    hand->move_vertical(hand, this->render_config_menu_options(this, renderer, hand, hand->current_state));
}
static int _render_config_menu_options(Menu *this, struct SDL_Renderer *renderer, Hand *hand, int current_state)
{
    int skip, i;
    char font_path[] = "ponde___.ttf";

    char rgb_matrix[3][50];
    Window **rgb_bars = (Window **)malloc(sizeof(Window *) * 3);

    skip = 20;
    rgb_bars[0] = CREATE_WINDOW(110, skip, 150, 15);
    rgb_bars[1] = CREATE_WINDOW(110, skip * 2, 150, 15);
    rgb_bars[2] = CREATE_WINDOW(110, skip * 3, 150, 15);

    rgb_bars[0]->color_value = MENU_BACKGROUND.r;
    rgb_bars[1]->color_value = MENU_BACKGROUND.g;
    rgb_bars[2]->color_value = MENU_BACKGROUND.b;

    rgb_bars[0]->color_bar_color = RED;
    rgb_bars[1]->color_bar_color = GRN;
    rgb_bars[2]->color_bar_color = BLU;

    sprintf(rgb_matrix[0], "RED                          %d", (int)MENU_BACKGROUND.r);
    sprintf(rgb_matrix[1], "GREEN                        %d", (int)MENU_BACKGROUND.g);
    sprintf(rgb_matrix[2], "BLUE                         %d", (int)MENU_BACKGROUND.b);

    this->font = TTF_OpenFont(font_path, 10);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    this->rect.x = 50;
    this->rect.y = skip;

    for (i = 0; i < 3; i++)
    {
        rgb_bars[i]->render_color_bar(rgb_bars, renderer, this->rect.x, this->rect.y, skip, i);

        TTF_SizeText(this->font, rgb_matrix[i], &this->rect.w, &this->rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, rgb_matrix[i], WHITE);
            this->change_window_color(rgb_bars, i);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, rgb_matrix[i], GREY);
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

void _change_window_color(Window **color_bars, int current_state)
{
    if (current_state == 0)
        MENU_BACKGROUND.r = color_bars[0]->adjust_menu_colors(color_bars[0]);
    else if (current_state == 1)
        MENU_BACKGROUND.g = color_bars[1]->adjust_menu_colors(color_bars[1]);
    else
        MENU_BACKGROUND.b = color_bars[2]->adjust_menu_colors(color_bars[2]);
}
static void _render_save_menu(Menu *this, struct SDL_Renderer *renderer, Hand *hand)
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
    hand->change_state_quantity(hand, 2, 0);
    this->main_menu_bg->render(this->main_menu_bg, renderer);
    hand->move_vertical(hand, this->render_save_menu_options(this, renderer, hand, hand->current_state));
}

static int _render_save_menu_options(Menu *this, struct SDL_Renderer *renderer, Hand *hand, int current_state)
{

    int skip, num_saves;
    char font_path[] = "ponde___.ttf";
    skip = 90;
    num_saves = 3;
    this->rect.x = 55;
    this->rect.y = 40;
    this->font = TTF_OpenFont(font_path, 10);
    for (size_t i = 0; i < num_saves; i++)
    {
        this->load_save_bg[i]->render(this->load_save_bg[i], renderer);
        TTF_SizeText(this->font, LOAD_SAVE_INFO_STRINGS[i]->list[0], &this->rect.w, &this->rect.h);
        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, LOAD_SAVE_INFO_STRINGS[i]->list[0], WHITE);
        }
        else
        {
            this->surface = TTF_RenderText_Solid(this->font, LOAD_SAVE_INFO_STRINGS[i]->list[0], GREY);
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

Menu *CREATE_MENU()
{
    Menu *this = (Menu *)malloc(sizeof(*this));

    this->destroy = _destroy;

    this->render_main_menu = _render_main_menu;
    this->render_main_menu_options = _render_main_menu_options;
    this->render_character_stats = _render_character_stats;
    this->render_character_main_menu_image = _render_character_main_menu_image;

    this->render_items_menu = _render_items_menu;
    this->render_items_menu_options = _render_items_menu_options;
    this->render_use_item_menu = _render_use_item_menu;

    this->render_config_menu = _render_config_menu;
    this->render_config_menu_options = _render_config_menu_options;
    this->change_window_color = _change_window_color;

    this->render_save_menu = _render_save_menu;
    this->render_save_menu_options = _render_save_menu_options;

    this->main_menu_bg = CREATE_WINDOW(12, 8, 336, 306);
    this->select_character_bg = CREATE_WINDOW(12, 200, 336, 120);
    this->load_save_bg = malloc(sizeof(Window *) * 3);
    this->load_save_bg[0] = CREATE_WINDOW(40, 30, 280, 75);
    this->load_save_bg[1] = CREATE_WINDOW(40, 120, 280, 75);
    this->load_save_bg[2] = CREATE_WINDOW(40, 210, 280, 75);
    this->font = NULL;
    this->surface = NULL;
    this->texture = NULL;
    this->option_states = 6;
    this->transition.x = 0;
    this->transition.y = 0;
    this->transition.w = WINDOW_WIDTH;
    this->transition.h = WINDOW_HEIGHT;
    this->item_being_used = 0;
    this->previous_number_of_states = 0;
    return this;
}