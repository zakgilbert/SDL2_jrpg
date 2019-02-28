/**
 * Affect.c
 */

#include "Affect.h"

int revive(int num, Character *character)
{
    if (character->HP.current > 1)
    {
        return 0;
    }
    character->HP.current += num;
    if (character->HP.current > character->HP.max)
    {
        character->HP.current = character->HP.max;
    }
    return 1;
}

int affect_mp(int num, Character *character)
{
    if(character->MP.current >= character->MP.max)
    {
        return 0;
    }
    character->MP.current += num;
    if (character->MP.current > character->MP.max)
    {
        character->MP.current = character->MP.max;
    }
    return 1;
}
int affect_hp(int num, Character *character)
{
    if (character->HP.current < 1 || character->HP.current >= character->HP.max)
    {
        return 0;
    }
    character->HP.current += num;
    if (character->HP.current > character->HP.max)
    {
        character->HP.current = character->HP.max;
    }
    return 1;
}

static void __destroy(Affect *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static int __cause_affect(Affect *this)
{
    switch (this->affect_enum)
    {
    case POTION:
        this->item_used = affect_hp(50, this->character);
        break;
    case ETHER:
        this->item_used = affect_mp(25, this->character);
        break;
    case PHOENIX_DOWN:
        this->item_used = revive(50, this->character);
        break;
    default:
        break;
    }
    return this->item_used;
}

Affect *CREATE_AFFECT(ITEM_ENUM affect, Character *character)
{

    Affect *this = (Affect *)malloc(sizeof(*this));
    this->cause_affect = __cause_affect;
    this->destroy = __destroy;
    this->affect_enum = affect;
    this->character = character;
    this->item_used = 0;

    return this;
}
