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

ITEM_ENUM query_affects(const char * str)
{
    printf("\n query affect_hp");
    for(int i = 0; i < ITEM_QUANTITY; i++)
    {
        printf("\ni is %d and item is %s", i, ITEMS[i]);
        if(strcmp(ITEMS[i], str)){
            printf("\n%s has been found a", str);
        
            return 0;
        }
    }
    printf("%s not found in ITEMS something is wrong.", str);
    return 0;
    
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

Affect *CREATE_AFFECT(const char * str, Character *character)
{

    Affect *this = (Affect *)malloc(sizeof(*this));
    this->cause_affect = __cause_affect;
    this->destroy = __destroy;
    this->affect = query_affects(str);
    this->character = character;

    return this;
}
