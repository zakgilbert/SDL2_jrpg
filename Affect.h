#ifndef JRPG_AFFECT_H
#define JRPG_AFFECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Character.h"
#include "header.h"
#include "Words.h"

void affect_hp(int, Character *);

typedef struct __affect
{
    void (*destroy) (struct __affect *);
    void (*cause_affect) (struct __affect *);
    Character * character;
    ITEM_ENUM affect_enum;
    int item_used;
}Affect;

Affect * CREATE_AFFECT(ITEM_ENUM , Character *);

#endif