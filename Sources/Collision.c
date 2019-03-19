#include "Collision.h"

static void _destroy(Collision *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _add_collision(Collision *this, Lootable **lootables, int num_lootables, int num_collidables, int area_key)
{
    this->num_collibables[area_key] = num_collidables;
    this->collidables[area_key] = malloc(sizeof(struct Collidable *) * num_collidables);
    if (NULL != lootables)
    {
        this->add_lootables(this, lootables, num_lootables, area_key);
    }
}
static void _add_lootables(Collision *this, Lootable **lootables, int num_lootables, int area_key)
{
    for (int k = 0; k < num_lootables; k++)
    {
        this->collidables[area_key][this->current_index] = malloc(sizeof(struct Collidable));
        this->collidables[area_key][this->current_index]->rect = malloc(sizeof(struct SDL_Rect));
        this->collidables[area_key][this->current_index]->rect = &lootables[k]->rect;
        this->collidables[area_key][this->current_index]->x = lootables[k]->x;
        this->collidables[area_key][this->current_index]->y = lootables[k]->y;
        this->collidables[area_key][this->current_index]->index = this->current_index;
        lootables[k]->index = this->current_index;
        this->current_index++;
    }
}

static void _update_collidables(Collision *this, int area_key)
{
    for (int k = 0; k < this->num_collibables[area_key]; k++)
    {
        this->collidables[area_key][k]->rect->x = ((this->collidables[area_key][k]->x) - X);
        this->collidables[area_key][k]->rect->y = ((this->collidables[area_key][k]->y) - Y);
    }
}

Collision *CREATE_COLLISION()
{
    Collision *this = malloc(sizeof(*this));
    this->add_collision = _add_collision;
    this->add_lootables = _add_lootables;
    this->update_collidables = _update_collidables;
    this->destroy = _destroy;
    this->collidables = malloc(sizeof(struct Collidable **) * NUM_AREAS);
    this->num_collibables = malloc(sizeof(int) * NUM_AREAS);
    this->current_index = 0;

    return this;
}