
/************************
	 *  Ba.c
	*/

#include "Ba.h"

void create_battle_textures(void *obj, struct SDL_Renderer *renderer)
{
    Ba *this = (Ba *)obj;
    this->create_textures(this, renderer);
    SDL_Delay(100);
}
void render_back_ground_texture(void *obj, struct SDL_Renderer *renderer)
{
    struct Texture *this = (struct Texture *)obj;
    SDL_RenderCopy(renderer, this->t, NULL, &this->r);
}
static void _destroy(Ba *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _create_textures(Ba *this, struct SDL_Renderer *renderer)
{
    int time_bar_x, time_bar_y, i, k;
    time_bar_x = 290;
    time_bar_y = 250;
    this->back_ground->t = create_texture(renderer, BATTLE_BACKGROUNDS->list[this->area], &this->back_ground->r);

    for (i = 0; i < this->num_enemies; i++)
    {
        this->enemies[i] = load_enemy(BATTLE_LINEUP[this->area]->list[this->roll][i], renderer);
        this->enemies[i]->rect.x = 35;
        this->enemies[i]->rect.y = (WINDOW_HEIGHT / 2) - 50;
    }
    for (k = 0; k < NUM_CHARACTERS; k++)
    {
        this->time_bars[k] = CREATE_WINDOW(time_bar_x, time_bar_y, 50, 8);
        this->time_bars[k]->rect.w = 0;
        time_bar_y += 15;
    }
}
static void _update(Ba *this)
{
    int i, status;
    if (CANCEL())
    {
        state = previous_state;
        previous_state = BATTLE;
        this->q->free(this->q);
        this->first_render = 1;
        NUM_STEPS = 0;
        return;
    }
    if (this->first_render)
    {
        ENQUEUE(this->q, this, create_battle_textures, NULL);
        this->q->copy(this->q);
        this->free_thread = SDL_CreateThread(free_handler, "free_handler", this->q);
        this->first_render = 0;
        MOVEMENT_DISABLED = 1;
        return;
    }
    SDL_WaitThread(this->free_thread, &status);
    ENQUEUE(this->q, this->back_ground, render_back_ground_texture, NULL);
    ENQUEUE(this->q, this->window, render_window, NULL);
    ENQUEUE(this->q, this->window, render_window, NULL);

    for (i = 0; i < this->num_enemies; i++)
    {
        ENQUEUE(this->q, this->enemies[i], render_enemy, NULL);
    }
    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        ENQUEUE(this->q, this->party[i], this->party[i]->render_battle_textures, NULL);
    }
    this->q->copy(this->q);
    this->free_thread = SDL_CreateThread(free_handler, "free_handler", this->q);
}
Ba *CREATE_BA(int area, int roll, Character **party)
{
    Ba *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->create_textures = _create_textures;
    this->update = _update;

    this->party = party;

    this->first_render = 1;

    this->roll = roll;
    this->area = area;
    this->action_window = NULL;
    this->back_ground = malloc(sizeof(struct Texture));
    this->back_ground->r.x = 0;
    this->back_ground->r.y = 0;
    this->time_bars = (Window **)malloc(sizeof(Window *) * NUM_CHARACTERS);
    this->q = CREATE_RENDER_Q();
    this->window = CREATE_WINDOW(5, 240, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 245);
    this->num_enemies = BATTLE_LINEUP[this->area]->num_ints[this->roll];
    this->enemies = (Enemy **)malloc(sizeof(Enemy *) * this->num_enemies);

    return this;
}
