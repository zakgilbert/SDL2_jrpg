#ifndef JRPG_AFFECT_H
#define JRPG_AFFECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "Words.h"
#include "Atlas.h"
#include "Character.h"

int affect_hp(int, Character *);
int affect_mp(int, Character *);
int revive(int, Character *);

typedef struct __affect
{
    void (*destroy)(struct __affect *);
    int (*cause_affect)(struct __affect *);
    Character *character;
    ITEM_ENUM affect_enum;
    int item_used;
    int type;
} Affect;

Affect *CREATE_AFFECT(ITEM_ENUM, Character *);

#endif