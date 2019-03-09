#include "Collidable.h"
static SDL_Color my_color = {255, 66, 66};
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
            //printf("\nup");
            these[i]->unlocked = 0;
        }
        if (these[i]->check_down_edge(these[i]))
        {
            if (these[i]->unlocked != -1)
            {
                these[i]->unlocked = 1;
            }
            result = -1;
            EDGE_DETECTION[2] = 1;
        }
        if (these[i]->unlocked && (USER_INPUTS[4]))
        {
            if (these[i]->interact(these[i]))
            {
                result = i;
                printf("\nChest was looted at index %d in dungeon bag.", i);
            }
            else
            {
                result = -1;
                these[i]->unlocked = 0;
            }
            EDGE_DETECTION[2] = 1;
        }
        if (these[i]->check_left_edge(these[i]))
        {
            EDGE_DETECTION[1] = 1;
            //printf("\nleft");
            these[i]->unlocked = 0;
        }
        if (these[i]->check_right_edge(these[i]))
        {
            EDGE_DETECTION[0] = 1;
            //   printf("\nright");
            these[i]->unlocked = 0;
        }
    }
    return result;
}
static int _check_down_edge(Collidable *this)
{

    if ((this->rect_1.y >= this->bottem.y_1) && (this->rect_1.y <= this->bottem.y_2) && (this->rect_1.x <= this->bottem.x_1) && (this->rect_1.x >= this->bottem.x_2))
    {
        return 1;
    }

    /*
    if (((this->rect_1.x - 162) < (22) && (this->rect_1.x - 162) > (((32 / 2) - (this->rect_1.w + (32 / 8))))) &&
        ((this->rect_1.y - 146) == ((32 / 2) - this->rect_1.h)))
    {
        return 1;
    }*/
    printf("\nthis->bottem.x_1: %d    this->rect_1.x:  %d", this->bottem.x_1, this->rect_1.x);
    printf("\nthis->bottem.y_1: %d    this->rect_1.y:  %d", this->bottem.y_1, this->rect_1.y);
    printf("\nthis->bottem.x_2: %d    this->rect_1.x:  %d", this->bottem.x_2, this->rect_1.x);
    printf("\nthis->bottem.y_2: %d    this->rect_1.y:  %d", this->bottem.y_2, this->rect_1.y);
    printf("\n____________________________________________________________________________________");
    return 0;
}

static int _check_up_edge(Collidable *this)
{
    if ((this->rect_1.y <= this->top.y_1) && (this->rect_1.y >= this->top.y_2) && (this->rect_1.x <= this->top.x_1) && (this->rect_1.x >= this->top.x_2))
    {
        my_color.r = 66;
        my_color.g = 255;
        my_color.b = 66;
        return 1;
    }
    /*
    if (((this->rect_1.x - 162) < (22) && (this->rect_1.x - 162) > (((32 / 2) - (this->rect_1.w + (32 / 8))))) &&
        ((this->rect_1.y - 146) == 26))
    {
        return 1;
    }*/
    return 0;
}
static int _check_left_edge(Collidable *this)
{
    if ((this->rect_1.x <= this->left.x_1) && (this->rect_1.x >= this->left.x_2) && (this->rect_1.y <= this->left.y_1) && (this->rect_1.y >= this->left.y_2))
    {
        printf("\nat left");
        my_color.r = 66;
        my_color.g = 255;
        my_color.b = 66;
        return 1;
    }

    /* printf("\nthis->left.x_1: %d    this->rect_1.x:  %d", this->left.x_1, this->rect_1.x);
    printf("\nthis->left.y_1: %d    this->rect_1.y:  %d", this->left.y_1, this->rect_1.y);
    printf("\nthis->left.x_2: %d    this->rect_1.x:  %d", this->left.x_2, this->rect_1.x);
    printf("\nthis->left.y_2: %d    this->rect_1.y:  %d", this->left.y_2, this->rect_1.y);
    printf("\n____________________________________________________________________________________");
    return 0; */
    /*
    if (((this->rect_1.y - 146) < (32) && (this->rect_1.y - 146) > (((32 / 2) - (this->rect_1.h + (32 / 8))))) &&
        ((this->rect_1.x - 162) == 22))
    {
        return 1;
    }
    return 0; */
    return 0;
}
static int _check_right_edge(Collidable *this)
{
    if ((this->rect_1.x >= this->right.x_1) && (this->rect_1.x <= this->right.x_2) && (this->rect_1.y <= this->right.y_1) && (this->rect_1.y >= this->right.y_2))
    {
        my_color.r = 66;
        my_color.g = 255;
        my_color.b = 66;
        return 1;
    }
    /*
    printf("\nthis->right.x_1: %d    this->rect_1.x:  %d", this->right.x_1, this->rect_1.x);
    printf("\nthis->right.y_1: %d    this->rect_1.y:  %d", this->right.y_1, this->rect_1.y);
    printf("\nthis->right.x_2: %d    this->rect_1.x:  %d", this->right.x_2, this->rect_1.x);
    printf("\nthis->right.y_2: %d    this->rect_1.y:  %d", this->right.y_2, this->rect_1.y);
    printf("\n____________________________________________________________________________________");
    if (((this->rect_1.y - 146) < (32) && (this->rect_1.y - 146) > (((32 / 2) - (this->rect_1.h + (32 / 8))))) &&
        ((this->rect_1.x - 162) == ((32 / 2) - this->rect_1.w)))
    {
        return 1;
    }
    */
    return 0;
}
static void _update_collidables(Collidable *this)
{
    this->rect_1.x = (this->x - X);
    this->rect_1.y = (this->y - Y);
    this->rect_2.x = this->rect_1.x;
    this->rect_2.y = this->rect_1.y + this->rect_2.h;
}
static void _render_collidables(Collidable **chests, Collidable **npcs, struct SDL_Renderer *renderer)
{
    int i, len, len_2, is_moving;
    is_moving = !(!USER_INPUTS[1] && !USER_INPUTS[2] && !USER_INPUTS[3]);
    len = chests[0]->number_of_collidables;
    if (USER_INPUTS[4])
    {
        SDL_SetRenderDrawColor(renderer, my_color.r, my_color.g, my_color.b, SDL_ALPHA_OPAQUE);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    }
    //   SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (i = 0; i < len; i++)
    {
        if (is_moving)
        {
            chests[i]->update_collidables(chests[i]);
        }
        SDL_RenderCopy(renderer, npcs[i]->first_texture, NULL, &npcs[i]->rect_1);
        SDL_RenderDrawRect(renderer, &npcs[i]->rect_2);
        SDL_RenderDrawLine(renderer, npcs[i]->left.x_1, npcs[i]->left.y_1, npcs[i]->left.x_2, npcs[i]->left.y_2);
        SDL_RenderDrawLine(renderer, npcs[i]->top.x_1, npcs[i]->top.y_1, npcs[i]->top.x_2, npcs[i]->top.y_2);
        SDL_RenderDrawLine(renderer, npcs[i]->right.x_1, npcs[i]->right.y_1, npcs[i]->right.x_2, npcs[i]->right.y_2);
        SDL_RenderDrawLine(renderer, npcs[i]->bottem.x_1, npcs[i]->bottem.y_1, npcs[i]->bottem.x_2, npcs[i]->bottem.y_2);
    }
    len_2 = npcs[0]->number_of_collidables;
    for (i = 0; i < len_2; i++)
    {
        if (is_moving)
        {
            npcs[i]->update_collidables(npcs[i]);
        }
        SDL_RenderCopy(renderer, chests[i]->first_texture, NULL, &chests[i]->rect_1);
        SDL_RenderDrawRect(renderer, &chests[i]->rect_2);
        SDL_RenderDrawLine(renderer, chests[i]->left.x_1, chests[i]->left.y_1, chests[i]->left.x_2, chests[i]->left.y_2);
        SDL_RenderDrawLine(renderer, chests[i]->top.x_1, chests[i]->top.y_1, chests[i]->top.x_2, chests[i]->top.y_2);
        SDL_RenderDrawLine(renderer, chests[i]->right.x_1, chests[i]->right.y_1, chests[i]->right.x_2, chests[i]->right.y_2);
        SDL_RenderDrawLine(renderer, chests[i]->bottem.x_1, chests[i]->bottem.y_1, chests[i]->bottem.x_2, chests[i]->bottem.y_2);
    }
}
static struct SDL_Rect *_make_chest(Collidable *this, struct SDL_Renderer *renderer, int x, int y, int w, int h)
{
    this->first_texture = this->create_collidable_texture(renderer, "graphics/chestClose.png", &this->rect_1);
    this->second_texture = this->create_collidable_texture(renderer, "graphics/chestOpen.png", &this->rect_1);
    this->rect_1.x = x;
    this->rect_1.y = y;
    this->rect_1.w = w;
    this->rect_1.h = h;
    this->x = x;
    this->y = y;

    this->rect_2.x = x;
    this->rect_2.y = y + (h / 2);
    this->rect_2.w = w;
    this->rect_2.h = h / 2;

    this->left.x_1 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->left.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->left.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->left.y_2 = (WINDOW_HEIGHT / 2);

    this->right.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->right.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->right.x_2 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->right.y_2 = (WINDOW_HEIGHT / 2);

    this->bottem.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->bottem.y_1 = (WINDOW_HEIGHT / 2);
    this->bottem.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->bottem.y_2 = (WINDOW_HEIGHT / 2);

    this->top.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->top.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->top.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->top.y_2 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);

    return &this->rect_1;
}
static void _make_npc(Collidable *this, struct SDL_Renderer *renderer, int x, int y, int w, int h, char *path)
{
    this->first_texture = this->create_collidable_texture(renderer, path, &this->rect_1);
    this->rect_1.x = x;
    this->rect_1.y = y;
    this->rect_1.w = w;
    this->rect_1.h = h;
    this->x = x;
    this->y = y;
    this->rect_2.x = x;
    this->rect_2.y = y + (h / 2);
    this->rect_2.w = w;
    this->rect_2.h = h / 2;

    this->left.x_1 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->left.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->left.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->left.y_2 = (WINDOW_HEIGHT / 2);

    this->right.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->right.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->right.x_2 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->right.y_2 = (WINDOW_HEIGHT / 2);

    this->bottem.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->bottem.y_1 = (WINDOW_HEIGHT / 2);
    this->bottem.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->bottem.y_2 = (WINDOW_HEIGHT / 2);

    this->top.x_1 = (WINDOW_WIDTH / 2) - (HERO_WIDTH / 4);
    this->top.y_1 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
    this->top.x_2 = (WINDOW_WIDTH / 2) + (HERO_WIDTH / 4);
    this->top.y_2 = (WINDOW_HEIGHT / 2) + (HERO_HEIGHT / 4);
}

static int _loot_chest(Collidable *this)
{
    if (!this->chest_was_looted)
    {
        MOVEMENT_DISABLED = 1;
        SDL_DestroyTexture(this->first_texture);
        this->first_texture = this->second_texture;
        this->chest_was_looted = 1;
        this->unlocked = -1;
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

Collidable *CREATE_COLLIDABLE(int type)
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
    this->update_collidables = _update_collidables;
    this->first_texture = NULL;
    this->second_texture = NULL;

    this->TYPE = type;
    this->collision_padding_x = (WINDOW_WIDTH / 2);
    this->collision_padding_y = (WINDOW_HEIGHT / 2);
    this->x = 0;
    this->y = 0;
    this->number_of_collidables = 0;
    this->unlocked = 0;
    /**
     * Lootable Item Section...chests and such.
     */
    this->make_chest = _make_chest;
    this->loot_chest = _loot_chest;
    this->chest_was_looted = 0;
    /**
     * NPCS
     */
    this->make_npc = _make_npc;
    return this;
}