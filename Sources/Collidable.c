#include "Collidable.h"
static void _destroy(Collidable *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static struct
    SDL_Texture *
    _create_collidable_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect *rect)
{
    struct SDL_Texture *texture = NULL;
    struct SDL_Surface *surface = NULL;

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
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    return texture;
}
static int _collistion(Collidable **these)
{
    int i, result, len;
    i = 0;
    result = -1;
    len = these[0]->number_of_collidables;

    for (i = 0; i < len; i++)
    {
        if (these[i]->check_up_edge(these[i]))
        {
            EDGE_DETECTION[3] = 1;
            printf("\nup");
            these[i]->ready_to_interact = 0;
        }
        if (these[i]->check_down_edge(these[i]))
        {
            these[i]->ready_to_interact = 1;
            result = -1;
            EDGE_DETECTION[2] = 1;
        }
        if (these[i]->ready_to_interact && (inputs[4]))
        {
            if (these[i]->interact(these[i]))
            {
                printf("\n-------------------%d", i);
                result = i;
            }
            else
            {
                result = -1;
                these[i]->ready_to_interact = 0;
            }
            EDGE_DETECTION[2] = 1;
        }
        if (these[i]->check_left_edge(these[i]))
        {
            EDGE_DETECTION[1] = 1;
            printf("\nleft");
            these[i]->ready_to_interact = 0;
        }
        if (these[i]->check_right_edge(these[i]))
        {
            EDGE_DETECTION[0] = 1;
            printf("\nright");
            these[i]->ready_to_interact = 0;
        }
    }
    return result;
}
static int _check_down_edge(Collidable *this)
{
    if (((this->rect_1.x - 162) < (22) && (this->rect_1.x - 162) > (((32 / 2) - (this->rect_1.w + (32 / 8))))) &&
        ((this->rect_1.y - 146) == ((32 / 2) - this->rect_1.h)))
    {
        return 1;
    }
    return 0;
}
static int _check_up_edge(Collidable *this)
{
    if (((this->rect_1.x - 162) < (22) && (this->rect_1.x - 162) > (((32 / 2) - (this->rect_1.w + (32 / 8))))) &&
        ((this->rect_1.y - 146) == 26))
    {
        return 1;
    }
    return 0;
}
static int _check_left_edge(Collidable *this)
{
    if (((this->rect_1.y - 146) < (32) && (this->rect_1.y - 146) > (((32 / 2) - (this->rect_1.h + (32 / 8))))) &&
        ((this->rect_1.x - 162) == 22))
    {
        return 1;
    }
    return 0;
}
static int _check_right_edge(Collidable *this)
{
    if (((this->rect_1.y - 146) < (32) && (this->rect_1.y - 146) > (((32 / 2) - (this->rect_1.h + (32 / 8))))) &&
        ((this->rect_1.x - 162) == ((32 / 2) - this->rect_1.w)))
    {
        return 1;
    }
    return 0;
}
static void _render_collidables(Collidable **these, struct SDL_Renderer *renderer, int mapX, int mapY)
{
    int i, len, is_moving;
    is_moving = !(!inputs[0] && !inputs[1] && !inputs[2] && !inputs[3]);
    len = these[0]->number_of_collidables;
    for (i = 0; i < len; i++)
    {
        if (is_moving)
        {
            update_collidables(&these[i]->rect_1, these[i]->x, these[i]->y, mapX, mapY);
        }
        SDL_RenderCopy(renderer, these[i]->first_texture, NULL, &these[i]->rect_1);
    }
}
static struct SDL_Rect *_make_chest(Collidable *this, struct SDL_Renderer *renderer, int x, int y, int w, int h)
{
    this->first_texture = this->create_collidable_texture(renderer, "graphics/chestClose.png", &this->rect_1);
    this->second_texture = this->create_collidable_texture(renderer, "graphics/chestOpen.png", &this->rect_2);
    this->rect_1.x = x;
    this->rect_1.y = y;
    this->rect_1.w = w;
    this->rect_1.h = h;
    this->x = x;
    this->y = y;
    return &this->rect_1;
}

static int _loot_chest(Collidable *this)
{
    if (!this->chest_was_looted)
    {
        MOVEMENT_DISABLED = 1;
        SDL_DestroyTexture(this->first_texture);
        this->first_texture = this->second_texture;
        printf("\n\n\nchest texture has been switched");
        this->chest_was_looted = 1;
        this->ready_to_interact = 0;
        return 1;
    }
    return 0;
}
static int _interact(Collidable *this)
{
    int result = 0;
    switch (this->TYPE)
    {
    case CHEST:
        result = this->loot_chest(this);
        break;
    case NPC:
        break;
    case ENEMY:
        break;
    case BUTTON:
        break;
    default:
        break;
    }
    return result;
}

Collidable *CREATE_COLLIDABLE(COLLIDABLE_TYPES)
{
    Collidable *this = (Collidable *)malloc(sizeof(*this));
    this->destroy = _destroy;
    this->create_collidable_texture = _create_collidable_texture;
    this->render_collidables = _render_collidables;
    this->collistion = _collistion;
    this->check_down_edge = _check_down_edge;
    this->check_up_edge = _check_up_edge;
    this->check_left_edge = _check_left_edge;
    this->check_right_edge = _check_right_edge;
    this->interact = _interact;
    this->first_texture = NULL;
    this->second_texture = NULL;

    this->TYPE = COLLIDABLE_TYPES;

    this->x = 0;
    this->y = 0;
    this->number_of_collidables = 0;
    this->ready_to_interact = 0;
    /**
     * Lootable Item Section...chests and such.
     */
    this->make_chest = _make_chest;
    this->loot_chest = _loot_chest;
    this->chest_was_looted = 0;
    return this;
}
void update_collidables(struct SDL_Rect *rect, int x, int y, int mapX, int mapY)
{
    rect->x = x - mapX;
    rect->y = y - mapY;
}