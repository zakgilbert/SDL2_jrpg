
/************************
 *  Battle.c
*/

#include "Battle.h"

uint32_t transition_delay1 = 200;
static const char *ACTION_STRS[] = {
    FOREACH_ACTION_OPTION(GENERATE_STRING)};

int calculate_time_bar(int seconds, int width)
{
    if ((FRAMES_RENDERED % (60 / (width / seconds))) == 0)
    {
        return 1;
    }
    return 0;
}

static int _update_time_bar(Window *time_bar, Character *character)
{
    int result = 0;
    if (time_bar->timer_is_maxed(time_bar))
    {
        character->in_action_queue = 1;
        result = 1;
    }
    else if (calculate_time_bar(character->SPD, time_bar->original_width))
    {
        time_bar->rect.w++;
    }
    return result;
}

static void _destroy(Battle *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _render_line(Battle *this, struct SDL_Renderer *renderer, const char *str, SDL_Color color)
{
    TTF_SizeText(this->font, str, &this->rect.w, &this->rect.h);
    this->surface = TTF_RenderText_Solid(this->font, str, color);
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
}

static int _render_action_menu_text(Battle *this, Character *character, struct SDL_Renderer *renderer, int i, int current_state)
{
    int skip, x, y, k;
    char font_path[] = "ponde___.ttf";

    this->font = TTF_OpenFont(font_path, 10);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    x = 200;
    y = 240;
    this->rect.x = x;
    this->rect.y = y;

    skip = TTF_FontLineSkip(this->font);
    for (k = 0; k < character->num_actions; k++)
    {
        if (k == current_state)
        {
            this->render_line(this, renderer, ACTION_STRS[character->actions[k]], GOLD);
        }
        else
        {
            this->render_line(this, renderer, ACTION_STRS[character->actions[k]], WHITE);
        }
        this->rect.y += skip;
    }

    TTF_CloseFont(this->font);
    return skip;
}
static int _render_battle_menu_text(Battle *this, struct SDL_Renderer *renderer, int index)
{
    int skip, x, y, i;
    char font_path[] = "ponde___.ttf";

    this->font = TTF_OpenFont(font_path, 10);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    x = 15;
    y = 250;
    this->rect.x = x;
    this->rect.y = y;
    skip = TTF_FontLineSkip(this->font);

    for (i = 0; i < this->num_enemies; i++)
    {
        this->render_line(this, renderer, ENEMIES->list[this->enemies[i]->key], WHITE);
        this->rect.y += skip;
    }
    this->rect.y = y - 1;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        this->party[i]->check_stats(this->party[i]);
        this->rect.x = 130;
        if (index == i)
        {
            this->render_line(this, renderer, this->party[i]->name, GOLD);
        }
        else
        {
            this->render_line(this, renderer, this->party[i]->name, WHITE);
        }
        this->rect.x += 60;
        this->render_line(this, renderer, this->party[i]->HP.display, WHITE);
        this->rect.y += skip + 4;
    }
    TTF_CloseFont(this->font);
    return 0;
}

static void _create_battle_textures(Battle *this, struct SDL_Renderer *renderer)
{
    int time_bar_x, time_bar_y, i, k;
    time_bar_x = 290;
    time_bar_y = 250;
    this->enemies = (Enemy **)malloc(sizeof(Enemy *) * this->num_enemies);

    for (i = 0; i < this->num_enemies; i++)
    {
        this->enemies[i] = load_enemy(BATTLE_LINEUP[this->area]->list[this->roll][i], renderer);
        this->enemies[i]->rect.x = 35;
        this->enemies[i]->rect.y = (WINDOW_HEIGHT / 2) - 50;
    }
    for (k = 0; k < this->num_party; k++)
    {
        this->party[k]->create_battle_textures(this->party[k], renderer, k);
        this->time_bars[k] = CREATE_WINDOW(time_bar_x, time_bar_y, 50, 8);
        this->time_bars[k]->rect.w = 0;
        time_bar_y += 15;
    }
}

static void _render(Battle *this, struct SDL_Renderer *renderer, Hand *hand)
{
    int i, k;

    if (!this->battle_rages_on)
    {
        state = previous_state;
        previous_state = BATTLE;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay1);
        NUM_STEPS = 0;
        return;
    }
    if (this->action_window == NULL)
    {
        this->action_window = CREATE_WINDOW(192, 230, 85, WINDOW_HEIGHT - 245);
    }
    SDL_RenderCopy(renderer, this->back_ground, NULL, &this->bg_rect);
    this->window->render(this->window, renderer);
    for (i = 0; i < this->num_enemies; i++)
    {
        this->enemies[i]->render(this->enemies[i], renderer);
    }
    for (k = 0; k < this->num_party; k++)
    {
        if (!this->party[k]->in_action_queue && this->update_time_bar(this->time_bars[k], this->party[k]))
        {
            this->q->add(this->q, this->party[k]->key, this->party[k]->type, k);
        }
        this->time_bars[k]->render_time_bar(this->time_bars[k], renderer);
        this->party[k]->render_battle_textures(this->party[k], renderer);
    }

    if (NULL == this->q->front)
    {
        this->render_battle_menu_text(this, renderer, -1);
    }
    else if (NULL != this->q->front)
    {
        this->render_battle_menu_text(this, renderer, this->q->front->index);
        hand->change_state_quantity(hand, this->party[this->q->front->index]->num_actions - 1, 0);
        this->action_window->render(this->action_window, renderer);
        hand->move_vertical(hand, this->render_action_menu_text(this, this->party[this->q->front->index], renderer, this->q->front->index, hand->current_state));
        if (USER_INPUTS[4])
        {
            this->time_bars[this->q->front->index]->rect.w = 0;
            this->party[this->q->front->index]->in_action_queue = 0;
            this->q->pop(this->q);
            USER_INPUTS[4] = 0;
            hand->current_state = 0;
        }
        else if (CANCEL())
        {
            this->q->re_q(this->q, this->q->pop(this->q));
            hand->current_state = 0;
        }
    }
    else
    {
        this->action_window->destroy(this->action_window);
        this->action_window = NULL;
    }
}

static int _battle_rages_on(Battle *this)
{
    int hp_tot, i;
    hp_tot = 0;

    for (i = 0; i < this->num_enemies; i++)
    {
        hp_tot += this->enemies[i]->HP.hp_current;
    }
    return hp_tot;
}

Battle *CREATE_BATTLE(int area, int roll, struct SDL_Renderer *renderer, Character **party, int num_party)
{
    Battle *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->create_battle_textures = _create_battle_textures;
    this->update_time_bar = _update_time_bar;
    this->render_battle_menu_text = _render_battle_menu_text;
    this->render_action_menu_text = _render_action_menu_text;
    this->render_line = _render_line;
    this->battle_rages_on = _battle_rages_on;

    this->bg_rect.x = 0;
    this->bg_rect.y = 0;
    this->party = party;
    this->num_party = num_party;
    this->party = party;
    this->back_ground = create_texture(renderer, BATTLE_BACKGROUNDS->list[area], &this->bg_rect);
    this->window = CREATE_WINDOW(5, 240, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 245);
    this->action_window = NULL;
    this->time_bars = (Window **)malloc(sizeof(Window *) * NUM_CHARACTERS);

    this->roll = roll;
    this->area = area;
    this->rect.x = 35;
    this->rect.y = (WINDOW_HEIGHT / 2) - 50;
    this->num_enemies = BATTLE_LINEUP[this->area]->num_ints[this->roll];
    this->create_battle_textures(this, renderer);
    this->transition.x = 0;
    this->transition.y = 0;
    this->transition.w = WINDOW_WIDTH;
    this->transition.h = WINDOW_HEIGHT;

    this->q = CREATE_BATTLE_Q();

    return this;
}