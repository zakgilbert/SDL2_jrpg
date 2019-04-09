#include "Menu.h"

uint32_t transition_delay = 200;

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static const char *MENU_OPTIONS[] = {
    FOREACH_MENU_OPTION(GENERATE_STRING)};
/**
    static void _render_line(Menu *this, struct SDL_Renderer *renderer, const char *str, SDL_Color color)
    {
        TTF_SizeText(this->font, str, &this->rect.w, &this->rect.h);
        this->surface = TTF_RenderText_Solid(this->font, str, color);
        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
        SDL_FreeSurface(this->surface);
        SDL_DestroyTexture(this->texture);
    }
*/
static int _set_main_menu_text_options(Menu *this, int _x, int _y, int size, int num_options)
{
    int skip, i, x, y;
    char font_path[] = "ponde___.ttf";
    this->font = TTF_OpenFont(font_path, size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font) + 6;
    x = _x;
    y = _y;

    for (i = 0; i < num_options; i++)
    {
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_TEXT(x, y, WHITE, this->font, MENU_OPTIONS[i]),
                         render_text));
        y += skip;
    }
    return skip;
}

static int _set_stat_text(Menu *this, int _x, int _y, int size, int key)
{
    int skip, i, x, y;
    char font_path[] = "ponde___.ttf";
    int prev_y;
    this->font = TTF_OpenFont(font_path, size);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    this->party[0]->update_party_stats(this->party);
    skip = TTF_FontLineSkip(this->font);
    x = _x;
    y = _y;
    prev_y = _y;

    switch (key)
    {
    case MAIN_MENU:
        for (i = 0; i < NUM_CHARACTERS; i++)
        {
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->name),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->age),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->job),
                             render_text));
            y = prev_y;
            x += 70;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->HP.display),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->MP.display),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->EXP.display),
                             render_text));
            x = _x;
            prev_y += 80;
            y = prev_y;
        }
        break;
    case USE_ITEM:
        for (i = 0; i < NUM_CHARACTERS; i++)
        {
            if (i == 2)
            {
                x = _x;
                y = _y + 50;
            }
            else if (i == 3)
            {
                y = _y + 50;
            }
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->name),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->HP.display),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->MP.display),
                             render_text));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font, this->party[i]->EXP.display),
                             render_text));
            x += 165;
            y = _y;
        }
        break;
    default:
        break;
    }
    return 0;
}
static void _set_character_main_menu_image(Menu *this)
{
    int i, j;

    j = 15;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        this->party[i]->rect.x = 20;
        this->party[i]->rect.w = 45;
        this->party[i]->rect.h = 45;
        this->party[i]->rect.y = j;
        this->q->add(this->q, this->q->new_node(this->party[i], render_character_bio_image));
        j += 80;
    }
}
static int _set_items_menu_options(Menu *this)
{
    int skip, i, x, y, quat_x, quat_y;
    char font_path[] = "ponde___.ttf";
    this->font = TTF_OpenFont(font_path, 10);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font);

    x = 49;
    y = 15;
    quat_x = 200;
    quat_y = 15;
    this->bag->update_quant_disp(this->bag);
    for (i = 0; i < this->bag->items_in_bag; i++)
    {
        this->q->add(this->q, this->q->new_node(CREATE_TEXT(
                                                    x, y, WHITE, this->font, ITEMS[this->bag->items[i]]),
                                                render_text));

        this->q->add(this->q, this->q->new_node(CREATE_TEXT(
                                                    quat_x, quat_y, WHITE, this->font, this->bag->get_display(this->bag, i)),
                                                render_text));
        quat_y += skip;
        y += skip;
    }
    return skip;
}
/**
static void _render_config_menu(Menu *this, struct SDL_Renderer *renderer)
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
    hand->move_vertical(hand, this->render_config_menu_options(this, renderer, hand, hand->current_state));
}
static int _set_config_menu_options(Menu *this)
{
    int skip, i;
    char font_path[] = "ponde___.ttf";

    char rgb_matrix[3][50];

    skip = 20;
    this->rgb_bars[0]->color_value = MENU_BACKGROUND.r;
    this->rgb_bars[1]->color_value = MENU_BACKGROUND.g;
    this->rgb_bars[2]->color_value = MENU_BACKGROUND.b;

    this->rgb_bars[0]->color_bar_color = RED;
    this->rgb_bars[1]->color_bar_color = GRN;
    this->rgb_bars[2]->color_bar_color = BLU;

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
        this->rgb_bars[i]->render_color_bar(this->rgb_bars, renderer, this->rect.x, this->rect.y, skip, i);

        TTF_SizeText(this->font, rgb_matrix[i], &this->rect.w, &this->rect.h);

        if (i == current_state)
        {
            this->surface = TTF_RenderText_Solid(this->font, rgb_matrix[i], WHITE);
            this->change_window_color(this->rgb_bars, i);
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
*/
/*
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

    int skip, num_saves, i;
    char font_path[] = "ponde___.ttf";
    skip = 90;
    num_saves = 3;
    this->rect.x = 55;
    this->rect.y = 40;
    this->font = TTF_OpenFont(font_path, 10);
    for (i = 0; i < num_saves; i++)
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

*/
static void _destroy(Menu *this)
{
    int i;

    this->main_menu_bg->destroy(this->main_menu_bg);
    this->select_character_bg->destroy(this->select_character_bg);
    for (i = 0; i < 3; i++)
    {
        this->rgb_bars[i]->destroy(this->rgb_bars[i]);
        this->load_save_bg[i]->destroy(this->load_save_bg[i]);
    }

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _set_q_main_menu(Menu *this)
{
    this->q->add(this->q, this->q->new_node(this->main_menu_bg, render_window));
    this->skip = this->set_main_menu_text_options(this, 270, 15, 12, 7);
    this->set_stat_text(this, 80, 15, 9, MAIN_MENU);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand));
    this->set_character_main_menu_image(this);
}
static void _update_main_menu(Menu *this)
{
    if (INPUT == CANCEL)
    {
        state = previous_state;
        previous_state = MAIN_MENU;
        INPUT = NONE;
        this->first_load = 1;
        r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition));
        return;
    }
    if (this->first_load == 1)
    {
        this->party[0]->update_party_stats(this->party);
        this->q->free(this->q);
        r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition));
        this->set_q_main_menu(this);
        this->first_load = 0;
    }

    this->hand->change_state_quantity(this->hand, this->option_states, 0);
    this->hand->move_vertical(this->hand, this->skip);
    MOVEMENT_DISABLED = 1;
    if (USER_INPUTS[4])
    {
        switch (this->hand->current_state)
        {
        case Items:
            state = ITEMS_MENU;
            this->hand->items_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition));
            this->set_q_items_menu(this);
            break;
        case Config:
            state = CONFIG;
            this->hand->config_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition));
            break;
            /**
            case Save:
                state = SAVE;
                this->hand->save_menu_position(this->hand);
                break;
            case Exit:
                INPUT = QUIT;
                break;
*/
        default:
            break;
        }
        USER_INPUTS[4] = 0;
    }
    this->q->copy(this->q);
}
static void _set_q_items_menu(Menu *this)
{
    this->q->add(this->q, this->q->new_node(this->main_menu_bg, render_window));
    this->skip = this->set_items_menu_options(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand));
}
static void _update_items_menu(Menu *this)
{

    if (INPUT == CANCEL)
    {
        state = MAIN_MENU;
        INPUT = NONE;
        this->hand->main_menu_position(this->hand);
        this->hand->current_state = 0;
        this->first_load = 1;
        return;
    }
    this->hand->change_state_quantity(this->hand, this->bag->items_in_bag - 1, 0);
    this->hand->move_vertical(this->hand, this->skip);
    MOVEMENT_DISABLED = 1;

    if (USER_INPUTS[4])
    {
        state = USE_ITEM;
        this->hand->use_item_position(this->hand);
        this->item_being_used = this->hand->current_state;
        this->hand->current_state = 0;
        this->previous_number_of_states = this->hand->number_of_states;
        this->q->add(this->q, this->q->new_node(this->select_character_bg, render_window));
        this->set_stat_text(this, 49, 205, 9, USE_ITEM);
        this->q->add(this->q, this->q->new_node(this->hand, render_hand));
        USER_INPUTS[4] = 0;
    }
    this->q->copy(this->q);
}

static void _update_use_items_menu(Menu *this)
{
    if (INPUT == CANCEL)
    {
        state = ITEMS_MENU;
        INPUT = NONE;
        this->hand->current_state = this->item_being_used;
        this->hand->items_menu_position(this->hand);
        this->hand->number_of_states = this->previous_number_of_states;
        this->q->free(this->q);
        this->set_q_items_menu(this);
        this->q->copy(this->q);
        return;
    }
    this->hand->change_state_quantity(this->hand, NUM_CHARACTERS - 1, 0);
    this->hand->vertical_horizontal(this->hand);

    if (USER_INPUTS[4])
    {
        int was_item_removed = this->bag->quaff_item(this->bag, CREATE_AFFECT(this->bag->items[this->item_being_used], this->party[this->hand->current_state]));

        this->previous_number_of_states += was_item_removed;
        if (was_item_removed == -1)
        {
            this->hand->items_menu_position(this->hand);
            this->hand->number_of_states = this->previous_number_of_states;
            state = ITEMS_MENU;
            INPUT = NONE;
            SDL_Delay(300);
        }
        this->q->free(this->q);
        this->set_q_items_menu(this);
        this->q->add(this->q, this->q->new_node(this->select_character_bg, render_window));
        this->set_stat_text(this, 49, 205, 9, USE_ITEM);
        this->q->add(this->q, this->q->new_node(this->hand, render_hand));
        USER_INPUTS[4] = 0;
    }
    this->q->copy(this->q);
}

static void _update_config(Menu *this)
{
}

Menu *CREATE_MENU(Character **party, Hand *hand, Item *bag)
{
    Menu *this = (Menu *)malloc(sizeof(*this));

    this->destroy = _destroy;

    this->update_main_menu = _update_main_menu;
    this->set_main_menu_text_options = _set_main_menu_text_options;
    this->set_stat_text = _set_stat_text;
    this->set_q_main_menu = _set_q_main_menu;
    this->set_character_main_menu_image = _set_character_main_menu_image;
    this->update_items_menu = _update_items_menu;
    this->set_items_menu_options = _set_items_menu_options;
    this->set_q_items_menu = _set_q_items_menu;
    this->update_use_items_menu = _update_use_items_menu;
    /**
    this->render_main_menu = _render_main_menu;
        this->render_main_menu_options = _render_main_menu_options;
        this->render_character_stats = _render_character_stats;
    
        this->render_items_menu = _render_items_menu;
        this->render_items_menu_options = _render_items_menu_options;
        this->render_use_item_menu = _render_use_item_menu;
    
        this->render_config_menu = _render_config_menu;
        this->render_config_menu_options = _render_config_menu_options;
        this->change_window_color = _change_window_color;
    
        this->render_save_menu = _render_save_menu;
        this->render_save_menu_options = _render_save_menu_options;
*/

    this->party = party;
    this->hand = hand;
    this->bag = bag;
    this->q = CREATE_RENDER_Q();

    this->main_menu_bg = CREATE_WINDOW(0, 0, 356, 326);
    this->select_character_bg = CREATE_WINDOW(12, 200, 336, 120);

    this->load_save_bg = (Window **)malloc(sizeof(Window *) * 3);
    this->load_save_bg[0] = CREATE_WINDOW(40, 30, 280, 75);
    this->load_save_bg[1] = CREATE_WINDOW(40, 120, 280, 75);
    this->load_save_bg[2] = CREATE_WINDOW(40, 210, 280, 75);

    this->rgb_bars = (Window **)malloc(sizeof(Window *) * 3);
    this->rgb_bars[0] = CREATE_WINDOW(110, 20, 150, 15);
    this->rgb_bars[1] = CREATE_WINDOW(110, 40, 150, 15);
    this->rgb_bars[2] = CREATE_WINDOW(110, 60, 150, 15);
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
    this->first_load = 1;
    this->skip = 0;
    this->delay = 100;
    this->set_q_main_menu(this);
    return this;
}

void render_transition(void *obj, struct SDL_Renderer *renderer)
{
    Uint32 ms = *(Uint32 *)obj;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(ms);
}