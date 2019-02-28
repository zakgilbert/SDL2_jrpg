
#ifndef JRPG_ITEM_H
#define JRPG_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "Affect.h"
#include "Words.h"
typedef struct _item
{
    void (*destroy)(struct _item *);
    void (*fill_bag)(struct _item *, const char **, int *, int);
    void (*add_item)(struct _item *, ITEM_ENUM);
    void (*quaff_item)(struct _item *, Affect *);
    int (*find_item)(struct _item *, ITEM_ENUM);
    void (*remove_item)(struct _item *, int);
    void (*decrement_item)(struct _item *, ITEM_ENUM);
    void (*loot)(struct _item *, ITEM_ENUM);
    ITEM_ENUM (*get_enum)(struct _item *, int);
    Affect * affect;
    char ** items;
    int * item_quantities;
    int items_in_bag;
}Items;

Items * CREATE_BAG();

#endif