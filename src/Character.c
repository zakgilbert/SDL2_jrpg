/* Character.c */

#include "Character.h"
#include "Battle_Q.h"

static const int hero_positions_x[4] = {240, 255, 270, 285};
static const int hero_positions_y[4] = {90, 120, 150, 180};

static const char *ACTION_STRS[] = {
    FOREACH_ACTION_OPTION(GENERATE_STRING)};

static const char *SPELL_STRS[] = {
    FOREACH_SPELL(GENERATE_STRING)};

static const char *FRMS[] = {
    FOREACH_CHARACTER_BATTLE_FRAME(GENERATE_STRING)};
/**
    static const int sched_spell[] = {pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, pray_1, pray_2, step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, cast_step, execute, execute, execute, execute, execute, execute, execute, fin};
*/

static void _destroy(Character *this)
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;

    if (NULL != this)
    {
        printf("freeing %s \n", this->name);
        free(this);
        this = NULL;
    }
}

static int prim_text(Character *this, Atlas *at, Render_Q *q)
{
    int skip, x, y, i;

    x = 200;
    y = 240;
    skip = 12;
    ENQUEUE(q, CREATE_LINE(at, this->name, x, y - 22), render_line0, NULL);
    for (i = 0; i < this->num_actions; i++)
    {
        ENQUEUE(q, CREATE_LINE(at, ACTION_STRS[this->actions[i]], x, y), render_line0, NULL);
        y += skip;
    }
    return skip;
}
static int spell_text(Character *this, Atlas *at, Render_Q *q)
{
    int skip, x, y, i;

    x = 208;
    y = 230;
    skip = 12;

    ENQUEUE(q, CREATE_LINE(at, this->name, x, y - 22), render_line0, NULL);
    for (i = 0; i < this->num_spells; i++)
    {
        ENQUEUE(q, CREATE_LINE(at, SPELL_STRS[this->spells[i]], x, y), render_line0, NULL);
        y += skip;
    }
    return skip;
}
static void _destroy_party(Character **party)
{
    int i;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        party[i]->destroy(party[i]);
    }
    free(party);
    party = NULL;
}

static int _update_party_stats(Character **these)
{
    int i;
    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        these[i]->check_stats(these[i]);
    }
    return 0;
}

static void _check_stats(Character *this)
{
    sprintf(this->HP.str_current, "%d", this->HP.current);
    sprintf(this->MP.str_current, "%d", this->MP.current);
    sprintf(this->EXP.str_current, "%d", this->EXP.current);
    strcat(strcat(strcat(strcpy(this->HP.display, this->HP.name), this->HP.str_current), "/"), this->HP.str_max);
    strcat(strcat(strcat(strcpy(this->MP.display, this->MP.name), this->MP.str_current), "/"), this->MP.str_max);
    strcat(strcat(strcat(strcpy(this->EXP.display, this->EXP.name), this->EXP.str_current), "/"), this->EXP.str_max);
}

static void _create_battle_texture(Character *this, struct SDL_Renderer *renderer, int i)
{
    char *str = malloc(40);
    strcpy(str, "Battle_Spr_");
    this->battle_spr = CREATE_SPRITE(str, BATTLE_CHARACTER_GRAPHICS->list[this->key], 2, 5, renderer, 10, FRMS, 32, 32);

    this->battle_spr->pos.x = hero_positions_x[i];
    this->battle_spr->pos.y = hero_positions_y[i];
}
static int _cast(Character *this, Render_Q *q)
{
    /**
    
        if (this->in_animation == -1)
        {
            this->in_animation = 1;
            this->current_animation_frame = 0;
            this->animation_total_frames = 39;
        }
        else if (this->current_animation_frame >= this->animation_total_frames)
        {
            this->in_animation = -1;
            this->curent_spell = animation_functions[no_ani];
            this->curent_spell(&this->b_rect_1, &this->b_rect_2, &this->index);
            this->current_state = waiting;
            return fin;
        }
        if (time_to_animate() && this->in_animation)
        {
            if (sched_spell[this->current_animation_frame] != execute)
            {
                this->curent_spell = animation_functions[sched_spell[this->current_animation_frame]];
                this->curent_spell(&this->b_rect_1, &this->b_rect_2, &this->index);
            }
            else
                animation_functions[no_ani](&this->b_rect_1, &this->b_rect_2, &this->index);
            this->current_animation_frame++;
        }
        if (sched_spell[this->current_animation_frame] == cast_step)
        {
            ENQUEUE(q, this->animation, this->animation->render_fire, NULL);
        }
    
        return sched_spell[this->current_animation_frame];
*/
}

static Uint32 _speed_round(Character *this)
{
    return (this->SPD / 10) * 10;
}
static void _render_battle_textures(void *obj, struct SDL_Renderer *renderer)
{
    Character *this = (Character *)obj;
    SDL_RenderCopy(renderer, this->battle_spr->texture,
                   this->battle_spr->search(
                       this->battle_spr, FRMS[this->current_sprite_frame]),
                   &this->battle_spr->pos);
}

static void _render_bio_image(Character *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}
static char *_get_data(void *obj)
{
    Character *this = (Character *)obj;
    char *data = malloc(100);
    char buffer[10];

    strcpy(data, this->name);
    strcat(data, "\n");
    strcat(data, this->name);
    strcat(data, ":   Current Battle State: ");
    sprintf(buffer, "%d", this->current_state);
    strcat(data, buffer);
    strcat(data, "\n");

    return data;
}
static int _get_current_state_options(Character *this)
{
    int num_states = 0;
    switch (this->current_state)
    {
    case primary:
        num_states = this->num_actions;
        break;
    case item:
        break;
    case magic:
        num_states = this->num_spells;
        break;
    default:
        break;
    }
    return num_states;
}
static int _set_battle_actions(Character *this, Atlas *at, Render_Q *q)
{
    switch (this->current_state)
    {
    case primary:
        ENQUEUE(q, BATTLE_PRIMARY(), render_window, NULL);
        return prim_text(this, at, q);
    case attack:
        break;
    case item:
        break;
    case magic:
        ENQUEUE(q, BATTLE_MAGIC(), render_window, NULL);
        return spell_text(this, at, q);
        break;
    default:
        break;
    }
    return 0;
}
Character *CREATE_CHARACTER(int key, struct SDL_Renderer *renderer)
{
    Character *this = (Character *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->check_stats = _check_stats;
    this->destroy_party = _destroy_party;
    this->update_party_stats = _update_party_stats;
    this->create_battle_texture = _create_battle_texture;
    this->render_battle_textures = _render_battle_textures;
    this->render_bio_image = _render_bio_image;
    this->speed_round = _speed_round;
    this->set_battle_actions = _set_battle_actions;
    this->get_current_state_options = _get_current_state_options;

    this->curent_spell = NULL;

    this->animation = CREATE_ANIMATION(renderer);
    this->cast = _cast;
    this->get_data = _get_data;
    this->key = key;
    this->num_stats = 1;
    this->in_action_queue = 0;
    this->type = PARTY_MEMBER;
    this->in_animation = -1;
    this->ani_i = 0;
    this->ready = 0;
    this->current_state = waiting;
    this->spells = malloc(sizeof(int) * 3);
    this->spells[0] = Fire;
    this->spells[1] = Ice;
    this->spells[2] = Bolt;
    this->num_spells = 3;
    this->current_sprite_frame = stand;

    strcpy(this->HP.name, "HP: ");
    strcpy(this->MP.name, "MP: ");
    strcpy(this->EXP.name, "EXP: ");

    /**
        this->create_battle_texture(this, renderer, this->key);
*/

    return this;
}
void render_character_bio_image(void *obj, struct SDL_Renderer *renderer)
{
    Character *this = (Character *)obj;
    this->render_bio_image(this, renderer);
}