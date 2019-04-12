
/************************
	 *  Me.c
	*/

#include "Me.h"

static const char *MENU_OPTIONS[] = {
    FOREACH_MENU_OPTION(GENERATE_STRING)};

static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static void _destroy(void *obj)
{
    Me *this = (Me *)obj;
    this->back_ground->destroy(this->back_ground);

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _set_main_menu(Me *this)
{
    this->q->free(this->q);
    this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
    this->skip = this->set_text_menu_options(this);
    this->set_text_stats(this);
    this->set_bio_image(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
}

static void _update_me(Me *this)
{
    if (CANCEL())
    {
        state = previous_state;
        previous_state = MAIN_MENU;
        this->time_to_load = 1;
        r_Q->add(r_Q, r_Q->new_node(&this->delay, menu_transition, NULL));

        return;
    }
    else if (this->time_to_load)
    {
        this->set_main_menu(this);
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
            /**
        case Config:
            state = CONFIG;
            this->hand->config_menu_position(this->hand);
            this->q->free(this->q);
            r_Q->add(r_Q, r_Q->new_node(&this->delay, menu_transition, NULL));
            this->set_q_config(this);
            break;
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
static int _set_text_menu_options(Me *this)
{
    int skip, i, x, y;

    skip = 19;
    x = 270;
    y = 15;

    for (i = 0; i < 7; i++)
    {
        this->q->add(this->q, this->q->new_node(
                                  CREATE_LINE(this->atlas, MENU_OPTIONS[i], x, y),
                                  render_line0, NULL));
        y += skip;
    }
    return skip;
}
static void _set_text_stats(Me *this)
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
                         render_line0, NULL));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->age, x, y),
                         render_line0, NULL));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->job, x, y),
                         render_line0, NULL));
        y = y_p;
        x += 70;

        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->HP.display, x, y),
                         render_line0, NULL));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->MP.display, x, y),
                         render_line0, NULL));
        y += skip;
        this->q->add(this->q,
                     this->q->new_node(
                         CREATE_LINE(this->atlas, this->party[i]->EXP.display, x, y),
                         render_line0, NULL));

        x = x_p;
        y_p += 80;
        y = y_p;
    }
}
static void _set_bio_image(Me *this)
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
static void _set_items_menu(Me *this)
{
    this->q->free(this->q);
    this->q->add(this->q, this->q->new_node(this->back_ground, render_window, NULL));
    this->skip = this->set_text_items_menu(this);
    this->q->add(this->q, this->q->new_node(this->hand, render_hand, NULL));
}
static void _update_items_menu(Me *this)
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

    this->q->copy(this->q);
}
static int _set_text_items_menu(Me *this)
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
                render_line0, NULL));

        this->q->add(
            this->q,
            this->q->new_node(
                CREATE_LINE(
                    this->atlas,
                    this->bag->get_display(this->bag, i),
                    quat_x, quat_y),
                render_line0, NULL));

        quat_y += skip;
        y += skip;
    }
    return skip;
}
Me *CREATE_ME(Character **party, Hand *hand, Item *bag, Atlas *atlas)
{
    Me *this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->update_me = _update_me;

    this->set_main_menu = _set_main_menu;
    this->set_text_menu_options = _set_text_menu_options;
    this->set_bio_image = _set_bio_image;

    this->set_text_stats = _set_text_stats;

    this->update_items_menu = _update_items_menu;
    this->set_items_menu = _set_items_menu;
    this->set_text_items_menu = _set_text_items_menu;

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