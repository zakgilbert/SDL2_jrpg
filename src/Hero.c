
#include "Hero.h"
static const char *keys[] = {
    "forstep1",
    "forstand",
    "forstep2",
    "backstep1",
    "backstand",
    "backstep2",
    "leftstep1",
    "leftstand",
    "leftstep2",
    "rightstep1",
    "rightstand",
    "rightstep2"};

static const char *dwn[] = {
    "forstand",
    "forstep1",
    "forstand",
    "forstep2",
};
static const char *upp[] = {
    "backstand",
    "backstep1",
    "backstand",
    "backstep2",
};
static const char *lft[] = {
    "leftstand",
    "leftstep1",
    "leftstand",
    "leftstep2",
};
static const char *rht[] = {
    "rightstand",
    "rightstep1",
    "rightstand",
    "rightstep2",
};
int get_middle_x(int frame_size, int sprite_size)
{
    return (frame_size / 2) - (sprite_size / 2);
}
int get_middle_y(int frame_size, int sprite_size)
{
    return (frame_size / 2) - (sprite_size / 2);
}

int time_to_animate()
{
    if (FRAMES_RENDERED % 7 == 0)
    {
        return 1;
    }
    return 0;
}

static void _destroy(Hero *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _render(Hero *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->sprite->texture, this->sprite->search(this->sprite, this->ani_buffer), &this->sprite->pos);
}

static void _animate_down(Hero *this)
{
    if (this->d_i == 4 || this->facing != down)
    {
        this->d_i = 0;
        this->facing = down;
    }
    free(this->ani_buffer);
    this->ani_buffer = strdup(dwn[this->d_i]);
    this->d_i++;
}

static void _animate_up(Hero *this)
{
    if (this->u_i == 4 || this->facing != up)
    {
        this->u_i = 0;
        this->facing = up;
    }
    free(this->ani_buffer);
    this->ani_buffer = strdup(upp[this->u_i]);
    this->u_i++;
}

static void _animate_left(Hero *this)
{
    if (this->l_i == 4 || this->facing != left)
    {
        this->l_i = 0;
        this->facing = left;
    }
    free(this->ani_buffer);
    this->ani_buffer = strdup(lft[this->l_i]);
    this->l_i++;
}

static void _animate_right(Hero *this)
{
    if (this->r_i == 4 || this->facing != right)
    {
        this->r_i = 0;
        this->facing = right;
    }
    free(this->ani_buffer);
    this->ani_buffer = strdup(rht[this->r_i]);
    this->r_i++;
}

static void _check_direction(Hero *this)
{
    if (key_state[SDL_SCANCODE_S])
    {
        this->animate_down(this);
    }
    else if (key_state[SDL_SCANCODE_W])
    {
        this->animate_up(this);
        this->facing = up;
    }
    else if (key_state[SDL_SCANCODE_A])
    {
        this->animate_left(this);
        this->facing = left;
    }
    else if (key_state[SDL_SCANCODE_D])
    {
        this->animate_right(this);
        this->facing = right;
    }
    else
    {
        switch (this->facing)
        {
        case down:
            free(this->ani_buffer);
            this->ani_buffer = strdup(keys[1]);
            break;
        case up:
            free(this->ani_buffer);
            this->ani_buffer = strdup(keys[4]);
            break;
        case left:
            free(this->ani_buffer);
            this->ani_buffer = strdup(keys[7]);
            break;
        case right:
            free(this->ani_buffer);
            this->ani_buffer = strdup(keys[10]);
            break;
        default:
            break;
        }
    }
}

static void _animate(Hero *this)
{
    if (time_to_animate() && !MOVEMENT_DISABLED)
    {
        this->check_direction(this);
    }
}

Hero *CREATE_HERO(Renderer renderer)
{
    Hero *this = (Hero *)malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;

    this->animate = _animate;
    this->check_direction = _check_direction;

    this->animate_down = _animate_down;
    this->animate_up = _animate_up;
    this->animate_left = _animate_left;
    this->animate_right = _animate_right;
    this->sprite = CREATE_SPRITE("Hero", "graphics/lockft.png", 4, 3, renderer, 12, keys, 18, 26);
    this->sprite->pos.x = get_middle_x(WINDOW_WIDTH, HERO_WIDTH);
    this->sprite->pos.y = get_middle_y(WINDOW_HEIGHT, HERO_HEIGHT);
    this->index = 0;
    this->facing = down;
    this->d_i = 0;
    this->u_i = 0;
    this->l_i = 0;
    this->r_i = 0;

    this->ani_buffer = strdup(keys[1]);
    return this;
}

void render_hero(void *obj, struct SDL_Renderer *renderer)
{
    Hero *this = (Hero *)obj;
    this->render(this, renderer);
}