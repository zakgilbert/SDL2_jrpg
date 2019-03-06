
#ifndef JRPG_ITEM_H
#define JRPG_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "Affect.h"
#include "Words.h"
#include "Message.h"
typedef struct _item
{
    void (*destroy)(struct _item *);
    void (*fill_bag)(struct _item *, const char [3][10], int *, int);
    char *(*add_item)(struct _item *, ITEM_ENUM);
    int (*quaff_item)(struct _item *, Affect *);
    int (*find_item)(struct _item *, ITEM_ENUM);
    int (*remove_item)(struct _item *, int);
    int (*decrement_item)(struct _item *, ITEM_ENUM);
    char *(*loot)(struct _item *, ITEM_ENUM);
    ITEM_ENUM(*get_enum)
    (struct _item *, int);
    Affect *affect;
    char **items;
    int *item_quantities;
    int items_in_bag;
} Items;

Items *CREATE_BAG();
#endif