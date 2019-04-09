
#include "Hero.h"

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
    if (FRAMES_RENDERED % 10 == 0)
    {
        return 1;
    }
    return 0;
}

static void _destroy(Hero *this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void _set_texture(Hero *this, struct SDL_Renderer *renderer, char *path)
{
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
    int width, height;

    surface = IMG_Load(path);
    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = HERO_WIDTH;
    this->rect.h = HERO_HEIGHT;
    this->rect_pos.x = get_middle_x(WINDOW_WIDTH, HERO_WIDTH);
    this->rect_pos.y = get_middle_y(WINDOW_HEIGHT, HERO_HEIGHT);
    this->rect_pos.w = HERO_WIDTH;
    this->rect_pos.h = HERO_HEIGHT;

    this->texture = texture;
}

static SDL_Rect *_get_rect_pointer(Hero *this)
{
    return &this->rect;
}

static SDL_Rect *_get_rect_pos_pointer(Hero *this)
{
    return &this->rect_pos;
}

static void _render(Hero *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, &this->rect, &this->rect_pos);
}

static void _animate_down(Hero *this)
{
    this->rect.y = 0;
    this->rect.x += this->rect.w;

    if (this->rect.x >= this->rect.w * 4)
    {
        this->rect.x = 0;
    }
}

static void _animate_up(Hero *this)
{
    this->rect.y = this->rect.h;
    this->rect.x += this->rect.w;

    if (this->rect.x >= this->rect.w * 4)
    {
        this->rect.x = 0;
    }
}

static void _animate_left(Hero *this)
{
    this->rect.y = this->rect.h * 2;
    this->rect.x += this->rect.w;

    if (this->rect.x >= this->rect.w * 4)
    {
        this->rect.x = 0;
    }
}

static void _animate_right(Hero *this)
{
    this->rect.y = this->rect.h * 3;
    this->rect.x += this->rect.w;

    if (this->rect.x >= this->rect.w * 4)
    {
        this->rect.x = 0;
    }
}

static void _check_direction(Hero *this)
{
    if (key_state[SDL_SCANCODE_S])
    {
        this->animate_down(this);
        FACING = DOWN;
    }
    else if (key_state[SDL_SCANCODE_W])
    {
        this->animate_up(this);
        FACING = UP;
    }
    else if (key_state[SDL_SCANCODE_A])
    {
        this->animate_left(this);
        FACING = LEFT;
    }
    else if (key_state[SDL_SCANCODE_D])
    {
        this->animate_right(this);
        FACING = RIGHT;
    }
}

static void _animate(Hero *this)
{
    if (time_to_animate() && !MOVEMENT_DISABLED)
    {
        this->check_direction(this);
    }
}

Hero *CREATE_HERO()
{
    Hero *this = (Hero *)malloc(sizeof(*this));
    this->set_texture = _set_texture;
    this->destroy = _destroy;
    this->render = _render;
    this->get_rect_pointer = _get_rect_pointer;
    this->get_rect_pos_pointer = _get_rect_pos_pointer;

    this->animate = _animate;
    this->check_direction = _check_direction;

    this->animate_down = _animate_down;
    this->animate_up = _animate_up;
    this->animate_left = _animate_left;
    this->animate_right = _animate_right;
    return this;
}

void render_hero(void *obj, struct SDL_Renderer *renderer)
{
    Hero *this = (Hero *)obj;
    this->render(this, renderer);
}