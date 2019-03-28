
/************************
 *  Battle.c
*/

#include "Battle.h"

uint32_t transition_delay1 = 200;

int calculate_time_bar(int seconds, int width)
{
    if ((FRAMES_RENDERED % (60 / (width / seconds))) == 0)
    {
        return 1;
    }
    return 0;
}

static void _update_time_bar(Window *time_bar, Character *character)
{
    if (calculate_time_bar(character->SPD, time_bar->original_width))
    {
        time_bar->rect.w++;
        if (time_bar->timer_is_maxed(time_bar))
        {
            time_bar->rect.w = 0;
        }
    }
}

static void _destroy(Battle *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _create_battle_textures(Battle *this, struct SDL_Renderer *renderer)
{
    int time_bar_x, time_bar_y;

    time_bar_x = 290;
    time_bar_y = 250;
    this->enemies = (Enemy **)malloc(sizeof(Enemy *) * this->num_enemies);
    this->textures_party = malloc(sizeof(struct SDL_Texture *) * NUM_CHARACTERS);
    for (size_t i = 0; i < this->num_enemies; i++)
    {
        this->enemies[i] = load_enemy(BATTLE_LINEUP[this->area]->list[this->roll][i], renderer);
        this->enemies[i]->rect.x = 35;
        this->enemies[i]->rect.y = (WINDOW_HEIGHT / 2) - 50;
    }
    for (size_t k = 0; k < this->num_party; k++)
    {
        this->textures_party[k] = create_texture(renderer, BATTLE_CHARACTER_GRAPHICS->list[k], &this->party_rect_2);
        this->time_bars[k] = CREATE_WINDOW(time_bar_x, time_bar_y, 50, 8);
        this->time_bars[k]->rect.w = 0;
        time_bar_y += 15;
    }
    this->party_rect_1.x = 240;
    this->party_rect_1.y = 90;
    this->party_rect_2.x = 0;
    this->party_rect_2.y = 0;
    this->party_rect_1.w = SPRITE_FRAME_WIDTH;
    this->party_rect_1.h = SPRITE_FRAME_HEIGHT;
    this->party_rect_2.w = SPRITE_FRAME_WIDTH;
    this->party_rect_2.h = SPRITE_FRAME_HEIGHT;
}

static void _render(Battle *this, struct SDL_Renderer *renderer)
{
    if (INPUT == CANCEL)
    {
        state = previous_state;
        previous_state = BATTLE;
        INPUT = NONE;
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &this->transition);
        SDL_RenderPresent(renderer);
        SDL_Delay(transition_delay1);
        NUM_STEPS = 0;
        return;
    }
    int party_x, party_y;
    party_x = this->party_rect_1.x;
    party_y = this->party_rect_1.y;
    SDL_RenderCopy(renderer, this->back_ground, NULL, &this->bg_rect);
    this->window->render(this->window, renderer);
    for (size_t i = 0; i < this->num_enemies; i++)
    {
        this->enemies[i]->render(this->enemies[i], renderer);
    }
    for (size_t k = 0; k < this->num_party; k++)
    {
        this->update_time_bar(this->time_bars[k], this->party[k]);
        SDL_RenderCopy(renderer, this->textures_party[k], &this->party_rect_2, &this->party_rect_1);
        this->time_bars[k]->render_time_bar(this->time_bars[k], renderer);
        this->party_rect_1.x += 15;
        this->party_rect_1.y += 30;
    }
    this->party_rect_1.x = party_x;
    this->party_rect_1.y = party_y;
}

Battle *CREATE_BATTLE(int area, int roll, struct SDL_Renderer *renderer, Character **party, int num_party)
{
    Battle *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->create_battle_textures = _create_battle_textures;
    this->update_time_bar = _update_time_bar;

    this->bg_rect.x = 0;
    this->bg_rect.y = 0;
    this->party = party;
    this->num_party = num_party;

    this->back_ground = create_texture(renderer, BATTLE_BACKGROUNDS->list[area], &this->bg_rect);
    this->window = CREATE_WINDOW(5, 240, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 245);

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
    return this;
}