#include "Menu.h"

uint32_t transition_delay = 200;

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static const char *MENU_OPTIONS[] = {
    FOREACH_MENU_OPTION(GENERATE_STRING)};


static int _set_main_menu_text_options(Menu *this, int _x, int _y, int size, int num_options)
{
    int skip, i, x, y;
    char font_path[] = "ponde.ttf";
    this->font_main_menu_options = TTF_OpenFont(font_path, 10);
    skip = TTF_FontLineSkip(this->font_main_menu_options) + 6;
    x = _x;
    y = _y;
    printf("Opening font_main_menu_options: %p\n", this->font_main_menu_options);
    for (i = 0; i < num_options; i++)
    {
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_TEXT(x, y, WHITE, this->font_main_menu_options, MENU_OPTIONS[i]),
                         render_text, text_destroy));
        y += skip;
    }
    return skip;
}

static void _set_stat_text(Menu *this, int _x, int _y, int size, int key)
{
    int skip, i, x, y;
    char font_path[] = "ponde.ttf";
    int prev_y;
    this->font_stats = TTF_OpenFont(font_path, 10);
    if (!this->font_stats)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    this->font_stats = this->font_stats;
    printf("Opening font_stats: %p\n", this->font_stats);
    this->party[0]->update_party_stats(this->party);
    skip = TTF_FontLineSkip(this->font_stats);
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
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->name),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->age),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->job),
                             render_text, text_destroy));
            y = prev_y;
            x += 70;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->HP.display),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->MP.display),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->EXP.display),
                             render_text, text_destroy));
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
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->name),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->HP.display),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->MP.display),
                             render_text, text_destroy));
            y += skip;
            this->q->add(this->q,
                         this->q->new_node(
                             CREATE_TEXT(x, y, WHITE, this->font_stats, this->party[i]->EXP.display),
                             render_text, text_destroy));
            x += 165;
            y = _y;
        }
        break;
    default:
        break;
    }
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
        this->q->add(this->q, this->q->new_node(this->party[i], render_character_bio_image, NULL));
        j += 80;
    }
}
static int _set_items_menu_options(Menu *this)
{
    int skip, i, x, y, quat_x, quat_y;
    char font_items_1_path[] = "ponde.ttf";
    this->font_items = TTF_OpenFont(font_items_1_path, 10);
    if (!this->font_items)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    printf("Opening font_items: %p\n", this->font_items);
    skip = TTF_FontLineSkip(this->font_items);
    x = 49;
    y = 15;
    quat_x = 200;
    quat_y = 15;
    this->bag->update_quant_disp(this->bag);
    for (i = 0; i < this->bag->items_in_bag; i++)
    {
        this->q->add(this->q, this->q->new_node(CREATE_TEXT(
                                                    x, y, WHITE, this->font_items, ITEMS[this->bag->items[i]]),
                                                render_text, text_destroy));

        this->q->add(this->q, this->q->new_node(CREATE_TEXT(
                                                    quat_x, quat_y, WHITE, this->font_items, this->bag->get_display(this->bag, i)),
                                                render_text, text_destroy));
        quat_y += skip;
        y += skip;
    }
    return skip;
}
/**
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
    char font_path[] = "ponde.ttf";
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
    this->q->add(this->q, this->q->new_node(this->main_menu_bg, render_window, NULL));
    this->set_stat_text(this, 80, 15, 9, MAIN_MENU);
    this->skip = this->set_main_menu_text_options(this, 270, 15, 12, 7);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
    this->set_character_main_menu_image(this);
}
static void _update_main_menu(Menu *this)
{
    if (CANCEL())
    {
        state = previous_state;
        previous_state = MAIN_MENU;
        this->first_load = 1;
        r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition, NULL));
        r_Q->add(r_Q, r_Q->new_node(this->font_main_menu_options, close_font, NULL));
        r_Q->add(r_Q, r_Q->new_node(this->font_stats, close_font, NULL));
        return;
    }
    if (this->first_load == 1)
    {
        this->party[0]->update_party_stats(this->party);
        this->q->free(this->q);
        r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition, NULL));
        this->set_q_main_menu(this);
        this->first_load = 0;
    }

    this->hand->change_state_quantity(this->hand, this->option_states, 0);
    this->hand->move_vertical(this->hand, this->skip);
    MOVEMENT_DISABLED = 1;
    if (CONFIRM())
    {
        switch (this->hand->current_state)
        {
        case Items:
            state = ITEMS_MENU;
            this->hand->items_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition, NULL));
            this->set_q_items_menu(this);
            break;
        case Config:
            state = CONFIG;
            this->hand->config_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, render_transition, NULL));
            this->set_q_config(this);
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
    }
    this->q->copy(this->q);
}
static void _set_q_items_menu(Menu *this)
{
    this->q->add(this->q, this->q->new_node(this->main_menu_bg, render_window, NULL));
    this->skip = this->set_items_menu_options(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
}
static void _update_items_menu(Menu *this)
{

    if (CANCEL())
    {
        state = MAIN_MENU;
        this->hand->main_menu_position(this->hand);
        this->hand->current_state = 0;
        this->first_load = 1;
        r_Q->add(r_Q, r_Q->new_node(this->font_items, close_font, NULL));
        return;
    }
    this->hand->change_state_quantity(this->hand, this->bag->items_in_bag - 1, 0);
    this->hand->move_vertical(this->hand, this->skip);
    MOVEMENT_DISABLED = 1;

    if (CONFIRM())
    {
        state = USE_ITEM;
        this->hand->use_item_position(this->hand);
        this->item_being_used = this->hand->current_state;
        this->hand->current_state = 0;
        this->previous_number_of_states = this->hand->number_of_states;
        this->q->free(this->q);
        this->set_items_menu_options(this);
        this->q->add(this->q, this->q->new_node(this->select_character_bg, render_window, NULL));
        this->set_stat_text(this, 49, 205, 9, USE_ITEM);
        this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
    }
    this->q->copy(this->q);
}

static void _update_use_items_menu(Menu *this)
{
    if (CANCEL())
    {
        state = ITEMS_MENU;
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

    if (CONFIRM())
    {
        int was_item_removed = this->bag->quaff_item(this->bag, CREATE_AFFECT(this->bag->items[this->item_being_used], this->party[this->hand->current_state]));

        this->previous_number_of_states += was_item_removed;
        if (was_item_removed == -1)
        {
            this->hand->items_menu_position(this->hand);
            this->hand->number_of_states = this->previous_number_of_states;
            state = ITEMS_MENU;
            SDL_Delay(300);
        }
        this->q->free(this->q);
        this->set_q_items_menu(this);
        this->q->add(this->q, this->q->new_node(this->select_character_bg, render_window, NULL));
        this->set_stat_text(this, 49, 205, 9, USE_ITEM);
        this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
        this->q->add(this->q, this->q->new_node(this->font_items, close_font, NULL));
        this->q->add(this->q, this->q->new_node(this->font_stats, close_font, NULL));
    }
    this->q->copy(this->q);
}

static void _set_q_config(Menu *this)
{
    this->q->add(this->q, this->q->new_node(this->main_menu_bg, render_window, NULL));
    this->skip = this->set_config_menu_options(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
}
static void _update_config(Menu *this)
{
    if (CANCEL())
    {
        state = MAIN_MENU;
        this->hand->main_menu_position(this->hand);
        this->first_load = 1;
        this->hand->current_state = 0;
        return;
    }
    MOVEMENT_DISABLED = 1;
    this->hand->change_state_quantity(this->hand, 2, 0);
    this->hand->move_vertical(this->hand, this->skip);
    this->q->free(this->q);
    this->set_q_config(this);
    this->q->copy(this->q);
}

static int _set_config_menu_options(Menu *this)
{
    int skip, i, x, y;
    this->font = TTF_OpenFont("ponde.ttf", 10);
    skip = 20;
    this->rgb_bars[0]->color_value = MENU_BACKGROUND.r;
    this->rgb_bars[1]->color_value = MENU_BACKGROUND.g;
    this->rgb_bars[2]->color_value = MENU_BACKGROUND.b;

    this->rgb_bars[0]->color_bar_color = RED;
    this->rgb_bars[1]->color_bar_color = GRN;
    this->rgb_bars[2]->color_bar_color = BLU;

    sprintf(this->rgb_matrix[0], "RED                          %d", (int)MENU_BACKGROUND.r);
    sprintf(this->rgb_matrix[1], "GREEN                        %d", (int)MENU_BACKGROUND.g);
    sprintf(this->rgb_matrix[2], "BLUE                         %d", (int)MENU_BACKGROUND.b);

    x = 50;
    y = skip;
    for (i = 0; i < 3; i++)
    {
        this->q->add(this->q, this->q->new_node(this->rgb_bars[i], render_window_color_bar, NULL));

        this->q->add(this->q, this->q->new_node(
                                  CREATE_TEXT(
                                      x, y, WHITE, this->font, this->rgb_matrix[i]),
                                  render_text, text_destroy));
        this->change_window_color(this->rgb_bars, this->hand->current_state);
        y += skip;
    }
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

    this->update_config = _update_config;
    this->set_config_menu_options = _set_config_menu_options;
    this->change_window_color = _change_window_color;
    this->set_q_config = _set_q_config;
    /**
    this->render_main_menu = _render_main_menu;
        this->render_main_menu_options = _render_main_menu_options;
        this->render_character_stats = _render_character_stats;
    
        this->render_items_menu = _render_items_menu;
        this->render_items_menu_options = _render_items_menu_options;
        this->render_use_item_menu = _render_use_item_menu;
    
        this->render_config_menu = _render_config_menu;
        this->render_config_menu_options = _render_config_menu_options;
    
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
    this->font_main_menu_options = NULL;
    this->font_stats = NULL;
    this->font_items = NULL;
    this->font_use_item = NULL;
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
    return this;
}

void render_transition(void *obj, struct SDL_Renderer *renderer)
{
    Uint32 ms = *(Uint32 *)obj;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(ms);
}