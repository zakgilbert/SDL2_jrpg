
/************************
	 *  Mog.c
	*/

#include "Mog.h"

static void _destroy(Mog *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
Mog *CREATE_MOG()
{
    Mog *this = malloc(sizeof(*this));

    return this;
}
