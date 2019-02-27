#ifndef JRPG_AFFECT_H
#define JRPG_AFFECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Character.h"
#include "Words.h"

void affect_hp(int, Character *);
ITEM_ENUM query_affects(const char *);

typedef struct __affect
{
    void (*destroy) (struct __affect *);
    void (*cause_affect) (struct __affect *);
    ITEM_ENUM affect;
    Character * character;
}Affect;

Affect * CREATE_AFFECT(const char *, Character *);

#endif