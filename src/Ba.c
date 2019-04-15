
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
    int i;
    if (NULL != this)
    {
        free(this);
        printf("destroying battle\n");
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
        this->party[i]->current_state = 0;
        printf("in create textures current state is %d\n", this->party[i]->current_state);
        /**
        
                this->time_bars[k] = CREATE_WINDOW(time_bar_x, time_bar_y, 50, 8);
                this->time_bars[k]->rect.w = 0;
                time_bar_y += 15;
*/
    }
}
static int _set_text_enemies(Ba *this)
{
    int skip, x, y, i;
    skip = 12;
    x = 15;
    y = 250;

    for (i = 0; i < this->num_enemies; i++)
    {
        ENQUEUE(this->q,
                CREATE_LINE(this->atlas, ENEMIES->list[this->enemies[i]->key], x, y),
                render_line0, NULL);
        y += skip;
    }
    return 0;
}
static Uint32 _hero_callback(Uint32 interval, void *param)
{
    struct timer_packet *tp = (struct timer_packet *)param;
    tp->ba->b->add(tp->ba->b, tp->c);
    printf("Hero Callback is being called\n");
    return 0;
}
static int _set_text_stats(Ba *this)
{
    int skip, x, y, l_x, i;
    skip = 12;
    x = 130;
    y = 250;
    l_x = x;

    this->party[0]->update_party_stats(this->party);

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        x = l_x;
        ENQUEUE(this->q,
                CREATE_LINE(this->atlas, this->party[i]->name, x, y),
                render_line0, NULL);

        x += 60;
        ENQUEUE(this->q,
                CREATE_LINE(this->atlas, this->party[i]->HP.display, x, y),
                render_line0, NULL);
        y += skip + 4;
    }
    return 0;
}
static void _update(Ba *this)
{
    int i, status;
    Character *head;
    if (CANCEL())
    {
        state = previous_state;
        previous_state = BATTLE;
        for (i = 0; i < NUM_CHARACTERS; i++)
        {
            while (SDL_RemoveTimer(this->hero_timers[i]))
                ;
            free(this->timer_packets[i]);
        }
        free(this->hero_timers);
        this->q->free(this->q);
        this->b->destroy(this->b);
        SDL_Delay(500);
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
    this->set_text_stats(this);
    this->set_text_enemies(this);

    for (i = 0; i < this->num_enemies; i++)
    {
        ENQUEUE(this->q, this->enemies[i], render_enemy, NULL);
    }
    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        if (this->party[i]->current_state == waiting)
        {
            this->timer_packets[i] = malloc(sizeof(struct timer_packet));
            this->timer_packets[i]->c = this->party[i];
            this->timer_packets[i]->ba = this;
            this->party[i]->current_state = in_timer;
            this->hero_timers[i] = SDL_AddTimer(this->party[i]->speed_round(this->party[i]), this->hero_callback, this->timer_packets[i]);
        }

        ENQUEUE(this->q, this->party[i], this->party[i]->render_battle_textures, NULL);
    }
    if (NULL != (head = this->b->peek(this->b, this->atlas, this->q)))
    {
        if (CONFIRM())
        {
            if (head->current_state == primary)
            {
                head->current_state = this->hand->current_state + 3;
                this->hand->current_state = 0;
            }
            else
            {
                this->b->pop(this->b);
                head->current_state = casting;
            }
        }
        this->hand->change_state_quantity(this->hand, head->get_current_state_options(head) - 1, 0);
        this->hand->move_vertical(this->hand, this->hand->battle_postion(this->hand, head->set_battle_actions(head, this->atlas, this->q), head->current_state));
        ENQUEUE(this->q, this->hand, render_hand, NULL);
    }

    this->q->copy(this->q);
    this->free_thread = SDL_CreateThread(free_handler, "free_handler", this->q);
}
Ba *CREATE_BA(int area, int roll, Character **party, Atlas *atlas, Hand *hand)
{
    Ba *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->create_textures = _create_textures;
    this->update = _update;
    this->set_text_stats = _set_text_stats;
    this->set_text_enemies = _set_text_enemies;
    this->hero_callback = _hero_callback;
    this->hero_timers = (SDL_TimerID *)malloc(sizeof(SDL_TimerID) * 1);
    this->party = party;
    this->first_render = 1;
    this->b = CREATE_BATTLE_Q();
    this->atlas = atlas;
    this->roll = roll;
    this->area = area;
    this->hand = hand;

    this->timer_packets = malloc(sizeof(struct timer_packet *) * 1);
    this->action_window = NULL;
    this->back_ground = malloc(sizeof(struct Texture));
    this->back_ground->r.x = 0;
    this->back_ground->r.y = 0;
    this->time_bars = (Window **)malloc(sizeof(Window *) * 1);
    this->q = CREATE_RENDER_Q();
    this->window = CREATE_WINDOW(5, 240, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 245);
    this->num_enemies = BATTLE_LINEUP[this->area]->num_ints[this->roll];
    this->enemies = (Enemy **)malloc(sizeof(Enemy *) * this->num_enemies);

    return this;
}
