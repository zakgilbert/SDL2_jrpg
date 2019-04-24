#ifndef MOG_H
#define MOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Mog
{
    void (*destroy)(struct _Mog *this);
} Mog;
Mog *CREATE_MOG();

#endif /* MOG_H */
