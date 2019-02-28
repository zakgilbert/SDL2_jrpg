#include "Collidable.h"
static void _destroy(Collidable * this)
{
    if(NULL != this)
    {
        free(this);
        this = NULL;
    }
}
Collidable * CREATE_COLLISION()
{
    Collidable * this = (Collidable *)malloc(sizeof(*this));
    this->destroy = _destroy;
    return this;
}