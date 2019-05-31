
#ifndef JRPG_ITEM_H
#define JRPG_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "Affect.h"
#include "Words.h"
#include "Atlas.h"

typedef struct _item
{

    void (*destroy)(struct _item *);
    void (*fill_bag)(struct _item *, int *items, int *quantities, int len);
    char *(*add_item)(struct _item *, ITEM_ENUM);
    int (*quaff_item)(struct _item *, Affect *);
    int (*find_item)(struct _item *, ITEM_ENUM);
    int (*remove_item)(struct _item *, int);
    int (*decrement_item)(struct _item *, ITEM_ENUM);
    const char *(*get_display)(struct _item *, int index);
    char *(*loot)(struct _item *, ITEM_ENUM);
    void (*update_quant_disp)(struct _item *this);
    Affect *affect;
    int *items;
    int *item_quantities;
    char **display;
    int items_in_bag;
} Item;

Item *CREATE_BAG();
#endif