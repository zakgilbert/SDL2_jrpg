#include "Collision.h"

void directions_restricted(int down, int up, int left, int right)
{
    EDGE_DETECTION[0] = down;
    EDGE_DETECTION[1] = up;
    EDGE_DETECTION[2] = left;
    EDGE_DETECTION[3] = right;
}
static void _destroy(Collision *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _add_collision(Collision *this, Lootable **lootables, int num_lootables, Npc **npcs, int num_npcs, int num_collidables, int area_key)
{
    this->num_collibables[area_key] = num_collidables;
    this->collidables[area_key] = malloc(sizeof(struct Collidable *) * num_collidables);
    if (NULL != lootables)
    {
        this->add_lootables(this, lootables, num_lootables, area_key);
    }
    if (NULL != npcs)
    {
        this->add_npcs(this, npcs, num_npcs, area_key);
    }
}
static int _check_down_edge(struct Collidable *collidable)
{
    if (((collidable->rect->x - COLLISION_X) < (22) && (collidable->rect->x - COLLISION_X) > (((32 / 2) - (collidable->rect->w + (32 / 8))))) &&
        ((collidable->rect->y - COLLISION_Y) == ((32 / 2) - collidable->rect->h)))
    {
        return 1;
    }
    return 0;
}
static int _check_up_edge(struct Collidable *collidable)
{
    if (((collidable->rect->x - COLLISION_X) < (22) && (collidable->rect->x - COLLISION_X) > (((32 / 2) - (collidable->rect->w + (32 / 8))))) &&
        ((collidable->rect->y - COLLISION_Y) == 26))
    {
        return 1;
    }
    return 0;
}
static int _check_left_edge(struct Collidable *collidable)
{
    if (((collidable->rect->y - COLLISION_Y) < (32) && (collidable->rect->y - COLLISION_Y) > (((32 / 2) - (collidable->rect->h + (32 / 8))))) &&
        ((collidable->rect->x - COLLISION_X) == 22))
    {
        return 1;
    }
    return 0;
}
static int _check_right_edge(struct Collidable *collidable)
{
    if (((collidable->rect->y - COLLISION_Y) < (32) && (collidable->rect->y - COLLISION_Y) > (((32 / 2) - (collidable->rect->h + (32 / 8))))) &&
        ((collidable->rect->x - COLLISION_X) == ((32 / 2) - collidable->rect->w)))
    {
        return 1;
    }
    return 0;
}
static void _add_lootables(Collision *this, Lootable **lootables, int num_lootables, int area_key)
{
    int k;
    for (k = 0; k < num_lootables; k++)
    {
        this->collidables[area_key][this->current_index] = malloc(sizeof(struct Collidable));
        this->collidables[area_key][this->current_index]->rect = &lootables[k]->rect;
        this->collidables[area_key][this->current_index]->x = lootables[k]->x;
        this->collidables[area_key][this->current_index]->y = lootables[k]->y;
        this->collidables[area_key][this->current_index]->index = this->current_index;
        this->collidables[area_key][this->current_index]->ready_to_interact = &lootables[k]->ready_to_interact;
        lootables[k]->index = this->current_index;
        this->current_index++;
    }
}
static void _add_npcs(Collision *this, Npc **npcs, int num_npcs, int area_key)
{
    int k;
    for (k = 0; k < num_npcs; k++)
    {
        this->collidables[area_key][this->current_index] = malloc(sizeof(struct Collidable));
        this->collidables[area_key][this->current_index]->rect = &npcs[k]->rect;
        this->collidables[area_key][this->current_index]->x = npcs[k]->x;
        this->collidables[area_key][this->current_index]->y = npcs[k]->y;
        this->collidables[area_key][this->current_index]->index = this->current_index;
        this->collidables[area_key][this->current_index]->ready_to_interact = &npcs[k]->ready_to_interact;
        npcs[k]->index = this->current_index;
        this->current_index++;
    }
}

static void _update_collidables(Collision *this, int area_key)
{
    int k, intersection;
    intersection = 0;
    if (area_key >= NUM_AREAS)
    {
        return;
    }
    for (k = 0; k < this->num_collibables[area_key]; k++)
    {

        if (SDL_HasIntersection(this->hero_rect, this->collidables[area_key][k]->rect))
        {
            intersection = 1;
            if (this->hero->facing == up)
            {
                Y--;
                *this->collidables[area_key][k]->ready_to_interact = 1;
            }
            if (this->hero->facing == down)
            {

                Y++;
                *this->collidables[area_key][k]->ready_to_interact = 0;
            }
            if (this->hero->facing == left)
            {
                X--;
                *this->collidables[area_key][k]->ready_to_interact = 0;
            }
            if (this->hero->facing == right)
            {
                X++;
                *this->collidables[area_key][k]->ready_to_interact = 0;
            }
        }
        else
        {
            *this->collidables[area_key][k]->ready_to_interact = 0;
        }
    }
}

static int _area_collision(Collision *this, int area_key)
{
    return 0;
}

Collision *CREATE_COLLISION(Hero *hero)
{
    Collision *this = malloc(sizeof(*this));
    this->add_collision = _add_collision;
    this->add_lootables = _add_lootables;
    this->add_npcs = _add_npcs;
    this->update_collidables = _update_collidables;
    this->area_collision = _area_collision;
    this->destroy = _destroy;

    this->check_down_edge = _check_down_edge;
    this->check_left_edge = _check_left_edge;
    this->check_right_edge = _check_right_edge;
    this->check_up_edge = _check_up_edge;

    this->hero_rect = &hero->sprite->pos;
    this->hero = hero;
    this->collidables = malloc(sizeof(struct Collidable **) * NUM_AREAS);
    this->num_collibables = malloc(sizeof(int) * NUM_AREAS);
    this->current_index = 0;

    return this;
}
int obj_mov_handler(void *ptr);