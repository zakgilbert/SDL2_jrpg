
#ifndef JRPG_ITEM_H
#define JRPG_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "Affect.h"

typedef struct _item
{
    void (*destroy)(struct _item *);
    void (*fill_bag)(struct _item *, const char **, int *, int);
    void (*refresh_bag)(struct _item *);
    void (*add_item)(struct _item *);
    void (*use_item)(struct _item *);

    char ** items;
    int * item_quantities;
    int items_in_bag;
}Items;

Items * CREATE_BAG();

#endif