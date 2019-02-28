/**
 * Affect.c
 */

#include "Affect.h"

void affect_hp(int num, Character *character)
{
    
    character->HP.current += num;
    if (character->HP.current > character->HP.max)
    {
        character->HP.current = character->HP.max;
    }
}

static void __destroy(Affect *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void __cause_affect(Affect *this)
{
    switch (this->affect_enum)
    {
    case POTION:
    printf("\nin cause_affect");
        affect_hp(50, this->character);
        this->item_used = 1;
        break;

    default:
        break;
    }
}

Affect *CREATE_AFFECT(ITEM_ENUM affect, Character *character)
{

    Affect *this = (Affect *)malloc(sizeof(*this));
    this->cause_affect = __cause_affect;
    this->destroy = __destroy;
    this->affect_enum = affect;
    this->character = character;
    this->item_used = 0;
    printf("\nAffect being used is %s and is at index %d", ITEMS[affect], affect);

    this->cause_affect(this);

    return this;
}
