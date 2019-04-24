
/************************
	 *  Menu.c
	*/

#include "Menu.h"

static const char *MENU_OPTIONS[] = {
    FOREACH_MENU_OPTION(GENERATE_STRING)};

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static void _destroy(void *obj)
{
    Menu *this = (Menu *)obj;
    int i;
    this->back_ground->destroy(this->back_ground);
    this->back_ground_use_item->destroy(this->back_ground_use_item);
    for (i = 0; i < 3; i++)
    {
        this->rgb_bars[i]->destroy(this->rgb_bars[i]);
    }

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _set_main_menu(Menu *this)
{
    this->q->free(this->q);
    this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
    this->skip = this->set_text_menu_options(this);
    this->set_text_stats(this);
    this->set_bio_image(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
}

static void _update_main(Menu *this)
{
    if (CANCEL())
    {
        state = previous_state;
        previous_state = MAIN_MENU;
        this->time_to_load = 1;
        this->q->free(this->q);
        r_Q->add(r_Q, r_Q->new_node(&this->delay, menu_transition, NULL));

        return;
    }
    else if (this->time_to_load)
    {
        this->set_main_menu(this);
        this->hand->main_menu_position(this->hand);
        this->hand->current_state = 0;
        this->time_to_load = 0;
    }
    this->hand->change_state_quantity(this->hand, 6, 0);
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
            r_Q->add(r_Q, r_Q->new_node(&this->delay, menu_transition, NULL));
            this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
            this->skip = this->set_text_items_menu(this);
            this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));

            break;
        case Config:
            state = CONFIG;
            this->hand->config_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, menu_transition, NULL));
            this->set_config(this);
            break;
        case Exit:
            key_state[O] = 1;
            break;
            /**
            case Save:
                state = SAVE;
                this->hand->save_menu_position(this->hand);
                break;
*/
        default:
            break;
        }
    }
    this->q->copy(this->q);
}
static int _set_text_menu_options(Menu *this)
{
    int skip, i, x, y;

    skip = 19;
    x = 290;
    y = 15;

    for (i = 0; i < 7; i++)
    {
        this->q->add(this->q, this->q->new_node(
                                  CREATE_LINE(this->atlas, MENU_OPTIONS[i], x, y),
                                  render_line, destroy_line));
        y += skip;
    }
    return skip;
}
static void _set_text_stats(Menu *this)
{
    int skip, i, x, y, y_p, x_p;

    skip = 12;
    x = 80;
    y = 15;
    y_p = y;
    x_p = x;

    this->party[0]->update_party_stats(this->party);
    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->name, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->age, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->job, x, y),
                         render_line, destroy_line));
        y = y_p;
        x += 70;

        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->HP.display, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->MP.display, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->EXP.display, x, y),
                         render_line, destroy_line));

        x = x_p;
        y_p += 80;
        y = y_p;
    }
}
static void _set_bio_image(Menu *this)
{
    int i, j;

    j = 15;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        this->party[i]->rect.x = 20;
        this->party[i]->rect.w = 45;
        this->party[i]->rect.h = 45;
        this->party[i]->rect.y = j;
        this->q->add(this->q, this->q->new_node(
                                  this->party[i], render_character_bio_image, NULL));

        j += 80;
    }
}
static int _set_items_menu(Menu *this)
{
    int skip;

    this->q->free(this->q);
    this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
    skip = this->set_text_items_menu(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));

    return skip;
}
static void _update_items_menu(Menu *this)
{
    if (CANCEL())
    {
        state = MAIN_MENU;
        this->hand->main_menu_position(this->hand);
        this->hand->current_state = 0;
        this->time_to_load = 1;

        return;
    }
    this->hand->change_state_quantity(this->hand, this->bag->items_in_bag - 1, 0);
    this->hand->move_vertical(this->hand, this->skip);
    MOVEMENT_DISABLED = 1;

    if (CONFIRM())
    {
        state = USE_ITEM;
        this->hand->use_item_position(this->hand);
        this->item_in_use = this->hand->current_state;
        this->hand->current_state = 0;
        this->previous_number_states = this->hand->number_of_states;
        this->q->free(this->q);
        this->set_items_menu(this);
        this->q->add(this->q, this->q->new_node(this->back_ground_use_item, render_window, NULL));
        this->set_text_use_item(this);

        this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
    }
    this->q->copy(this->q);
}
static int _set_text_items_menu(Menu *this)
{
    int i, skip, x, y, quat_x, quat_y;

    skip = 10;
    x = 49;
    y = 15;
    quat_x = 200;
    quat_y = 15;
    this->bag->update_quant_disp(this->bag);
    for (i = 0; i < this->bag->items_in_bag; i++)
    {
        this->q->add(
            this->q,
            this->q->new_node(
                CREATE_LINE(
                    this->atlas,
                    ITEMS[this->bag->items[i]], x, y),
                render_line, destroy_line));

        this->q->add(
            this->q,
            this->q->new_node(
                CREATE_LINE(
                    this->atlas,
                    this->bag->get_display(this->bag, i),
                    quat_x, quat_y),
                render_line, destroy_line));

        quat_y += skip;
        y += skip;
    }
    return skip;
}
static void _update_use_item(Menu *this)
{
    if (CANCEL())
    {
        state = ITEMS_MENU;
        this->hand->current_state = this->item_in_use;
        this->hand->items_menu_position(this->hand);
        this->hand->number_of_states = this->previous_number_states;
        this->q->free(this->q);
        this->skip = this->set_items_menu(this);
        this->q->copy(this->q);
        return;
    }
    this->hand->change_state_quantity(this->hand, NUM_CHARACTERS - 1, 0);
    this->hand->vertical_horizontal(this->hand);

    if (CONFIRM())
    {
        int was_item_removed = this->bag->quaff_item(
            this->bag, CREATE_AFFECT(
                           this->bag->items[this->item_in_use],
                           this->party[this->hand->current_state]));

        this->previous_number_states += was_item_removed;
        if (was_item_removed == -1)
        {
            this->hand->items_menu_position(this->hand);
            this->hand->number_of_states = this->previous_number_states;
            state = ITEMS_MENU;
            this->skip = this->set_items_menu(this);
            this->q->copy(this->q);
            SDL_Delay(300);
            return;
        }
        this->set_items_menu(this);
        this->q->add(this->q, this->q->new_node(this->back_ground_use_item, render_window, NULL));
        this->set_text_use_item(this);
        this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
    }
    this->q->copy(this->q);
}
static void _set_text_use_item(Menu *this)
{
    int i, x, y, y_p, x_p, skip;

    skip = 12;
    x = 49;
    y = 205;
    y_p = y;
    x_p = x;

    this->party[0]->update_party_stats(this->party);
    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        if (i == 2)
        {
            x = x_p;
            y = y_p + 58;
        }
        else if (i == 3)
            y = y_p + 58;

        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->name, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->HP.display, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->MP.display, x, y),
                         render_line, destroy_line));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->EXP.display, x, y),
                         render_line, destroy_line));

        x += 165;
        y = y_p;
    }
}
static void _update_config(Menu *this)
{
    if (CANCEL())
    {
        state = MAIN_MENU;
        this->hand->main_menu_position(this->hand);
        this->time_to_load = 1;
        this->hand->current_state = 0;
        return;
    }
    MOVEMENT_DISABLED = 1;
    this->hand->change_state_quantity(this->hand, 2, 0);
    this->hand->move_vertical(this->hand, this->skip);
    this->q->free(this->q);
    this->skip = this->set_config(this);
    this->q->copy(this->q);
}
static int _set_config(Menu *this)
{
    int skip;
    this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
    skip = this->set_text_config(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));

    return skip;
}
static int _set_text_config(Menu *this)
{
    int skip, i, x, y;
    skip = 21;

    this->rgb_bars[0]->color_value = MENU_BACKGROUND.r;
    this->rgb_bars[1]->color_value = MENU_BACKGROUND.g;
    this->rgb_bars[2]->color_value = MENU_BACKGROUND.b;

    this->rgb_bars[0]->color_bar_color = RED;
    this->rgb_bars[1]->color_bar_color = GRN;
    this->rgb_bars[2]->color_bar_color = BLU;

    sprintf(this->rgb_matrix[0],
            "RED                                      %d",
            (int)MENU_BACKGROUND.r);
    sprintf(this->rgb_matrix[1],
            "GREEN                                   %d",
            (int)MENU_BACKGROUND.g);
    sprintf(this->rgb_matrix[2],
            "BLUE                                     %d",
            (int)MENU_BACKGROUND.b);

    x = 50;
    y = skip;
    for (i = 0; i < 3; i++)
    {
        this->q->add(this->q, this->q->new_node(this->rgb_bars[i], render_window_color_bar, NULL));

        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->rgb_matrix[i], x, y),
                         render_line, destroy_line));

        this->update_window_color(this->rgb_bars, this->hand->current_state);
        y += skip;
    }
    return skip;
}
static void _update_window_color(Window **color_bars, int current_state)
{
    if (current_state == 0)
        MENU_BACKGROUND.r = color_bars[0]->adjust_menu_colors(color_bars[0]);
    else if (current_state == 1)
        MENU_BACKGROUND.g = color_bars[1]->adjust_menu_colors(color_bars[1]);
    else
        MENU_BACKGROUND.b = color_bars[2]->adjust_menu_colors(color_bars[2]);
}

Menu *CREATE_MENU(Character **party, Hand *hand, Item *bag, Atlas *atlas)
{
    Menu *this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->update_main = _update_main;

    this->set_main_menu = _set_main_menu;
    this->set_text_menu_options = _set_text_menu_options;
    this->set_bio_image = _set_bio_image;

    this->set_text_stats = _set_text_stats;

    this->update_items_menu = _update_items_menu;
    this->set_items_menu = _set_items_menu;
    this->set_text_items_menu = _set_text_items_menu;

    this->update_use_item = _update_use_item;
    this->set_text_use_item = _set_text_use_item;
    this->item_in_use = 0;
    this->previous_number_states = 0;
    this->back_ground_use_item = CREATE_WINDOW(12, 200, 336, 120);

    this->update_config = _update_config;
    this->set_config = _set_config;
    this->set_text_config = _set_text_config;
    this->update_window_color = _update_window_color;
    this->rgb_bars = (Window **)malloc(sizeof(Window *) * 3);
    this->rgb_bars[0] = CREATE_WINDOW(110, 20, 150, 15);
    this->rgb_bars[1] = CREATE_WINDOW(110, 40, 150, 15);
    this->rgb_bars[2] = CREATE_WINDOW(110, 60, 150, 15);

    this->q = CREATE_RENDER_Q();
    this->party = party;
    this->hand = hand;
    this->bag = bag;
    this->atlas = atlas;
    this->skip = 0;
    this->delay = 100;

    this->back_ground = CREATE_WINDOW(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->time_to_load = 1;

    return this;
}

void menu_transition(void *obj, struct SDL_Renderer *renderer)
{
    Uint32 ms = *(Uint32 *)obj;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(ms);
}