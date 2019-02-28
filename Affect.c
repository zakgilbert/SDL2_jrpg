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
    this->cause_affect(this);
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void __cause_affect(Affect *this)
{
printf("\nthis-affect %d\nPotion: %d", this->affect, Potion);
    switch (this->affect)
    {
    case Potion:
    printf("\nin cause_affect");
        affect_hp(50, this->character);
        ITEM_QUANTITIES[this->affect]--;
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
    this->affect = query_affects(str);
    this->character = character;

    return this;
}
