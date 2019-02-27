//
// Created by zachary on 1/27/19.
//

#include "Hand.h"

static void __destroy(Hand *this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

int animate_hand_thread(void *ptr)
{
    Hand *hand = ptr;
    int is_running = 1;

    while (is_running)
    {
        if (INPUT == QUIT)
        {
            is_running = 0;
            return 0;
        }
        if (TICK)
        {
            hand->animate(hand);
            TICK = 0;
        }
        SDL_Delay(1);
    }
    return 0;
}
static void __use_item_position(Hand *this)
{
    this->position.x = 15;
    this->position.y = 215;
}

static void __items_menu_position(Hand *this)
{
    this->position.x = 15;
    this->position.y = 11 + (11 * this->current_state);
}
static void __main_menu_position(Hand *this)
{
    this->position.x = 233;
    this->position.y = 11;
}

static void __render(Hand *this, struct SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->texture, this->get_rect_pointer(this), this->get_rect_pos_pointer(this));
}

static void __create_texture(Hand *this, char *path, struct SDL_Renderer *renderer, int x, int y)
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
    this->rect.w = 32;
    this->rect.h = 32;
    this->position.x = x;
    this->position.y = y;
    this->position.w = 32;
    this->position.h = 32;

    this->texture = texture;
}

static SDL_Rect *__get_rect_pos_pointer(Hand *this)
{
    return &this->position;
}

static SDL_Rect *__get_rect_pointer(Hand *this)
{
    return &this->rect;
}

static void __set_states(Hand *this, int state_00, int state_01, int state_10, int state_11, int state_20, int state_21, int state_30, int state_31)
{
    this->state_0[0] = state_00;
    this->state_0[1] = state_01;
    this->state_1[0] = state_10;
    this->state_1[1] = state_11;
    this->state_2[0] = state_20;
    this->state_2[1] = state_21;
    this->state_3[0] = state_30;
    this->state_3[1] = state_31;
}

int __change_state_quantity(Hand *this, int number, int add)
{
    if (add)
    {
        this->number_of_states += number;
    }
    else
    {
        this->number_of_states = number;
    }
    return this->number_of_states;
}

int __change_get_state(Hand *this, int number, int add)
{
    if (add)
    {
        this->current_state += number;
    }
    else
    {
        this->current_state = number;
    }
    return this->current_state;
}

static void __animate(Hand *this)
{
    if (FRAMES_RENDERED % 10 == 0)
    {
        this->rect.x += this->rect.w;

        if ((this->rect.x >= this->rect.w * 4) && (this->rect.y == 0))
        {
            this->rect.x = 0;
            this->rect.y = this->rect.h;
        }
        else if ((this->rect.x >= this->rect.w * 4) && (this->rect.y == this->rect.h))
        {
            this->rect.y = 0;
            this->rect.x = 0;
        }
    }
}

static int __move_horizontal(Hand *this, int distance)
{
    if (inputs[2] && this->current_state > 0)
    {
        this->position.x -= distance;
        this->current_state--;
    }
    else if (inputs[3] && this->current_state < this->number_of_states)
    {
        this->position.x += distance;
        this->current_state++;
    }
    return this->current_state;
}

static int __move_vertical(Hand *this, int distance)
{
    if (inputs[1] && this->current_state > 0)
    {
        this->position.y -= distance;
        this->current_state--;
        refresh_inputs(inputs, 6);
    }
    else if (inputs[0] && this->current_state < this->number_of_states)
    {
        this->position.y += distance;
        this->current_state++;
        refresh_inputs(inputs, 6);
    }
    return this->current_state;
}

static void __vertical_horizontal(Hand *this)
{
    switch (this->current_state)
    {
    case 0:
        if (inputs[0]) //down
        {
            this->position.y = this->state_2[1];
            this->current_state = 2;
            break;
        }
        else if (inputs[3]) // right
        {
            this->position.x = this->state_1[0];
            this->current_state = 1;
            break;
        }
        break;

    case 1:
        if (inputs[0]) //down
        {
            this->position.y = this->state_3[1];
            this->current_state = 3;
            break;
        }
        else if (inputs[2]) //left
        {
            this->position.x = this->state_0[0];
            this->current_state = 0;
            break;
        }
        break;

    case 2:
        if (inputs[1]) //up
        {
            this->position.y = this->state_0[1];
            this->current_state = 0;
            break;
        }
        else if (inputs[3]) //right
        {
            this->position.x = this->state_3[0];
            this->current_state = 3;
            break;
        }
        break;
    case 3:
        if (inputs[1]) //up
        {
            this->position.y = this->state_1[1];
            this->current_state = 1;
            break;
        }
        else if (inputs[2]) //left
        {
            this->position.x = this->state_2[0];
            this->current_state = 2;
            break;
        }
        break;
    }
}

Hand *CREATE_HAND()
{
    Hand *this = (Hand *)malloc(sizeof(*this));

    // -n>
    this->destroy = __destroy;
    this->render = __render;
    this->create_texture = __create_texture;
    this->animate = __animate;

    this->change_state_quantity = __change_state_quantity;
    this->change_get_state = __change_get_state;

    this->get_rect_pos_pointer = __get_rect_pos_pointer;
    this->get_rect_pointer = __get_rect_pointer;

    this->move_vertical = __move_vertical;
    this->move_horizontal = __move_horizontal;
    this->items_menu_position = __items_menu_position;
    this->main_menu_position = __main_menu_position;
    this->use_item_position = __use_item_position;
    this->vertical_horizontal = __vertical_horizontal;
    this->set_states = __set_states;
    // -o>
    this->set_states(this, 15, 215, 190, 215, 15, 265, 190, 265);
    this->current_state = 0;
    return this;
}
