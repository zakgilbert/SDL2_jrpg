
#include "Item.h"

static char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

static void _destroy(Items *this)
{
    if (this->items_in_bag > 1)
    {
        if (NULL != this->items)
        {
            free(this->items);
        }
        if (NULL != this->item_quantities)
        {
            free(this->item_quantities);
        }
    }
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _fill_bag(Items *this, int *items, int *quantities, int len)
{
    this->items = (int *)malloc(sizeof(int) * len);
    this->item_quantities = (int *)malloc(sizeof(int) * len);

    for (int i = 0; i < len; i++)
    {
        this->items[i] = items[i];
        if (NULL == quantities)
        {
            this->item_quantities[i] = 1;
        }
        else
        {
            this->item_quantities[i] = quantities[i];
        }
    }
    this->items_in_bag = len;
}
static char *_add_item(Items *this, ITEM_ENUM item_enum)
{
    size_t new_size = this->items_in_bag + 1;

    this->items = realloc(this->items, sizeof(int) * new_size);
    this->item_quantities = realloc(this->item_quantities, sizeof(int) * new_size);

    this->items[this->items_in_bag] = item_enum;
    this->item_quantities[this->items_in_bag] = 1;
    this->items_in_bag++;
    return ITEMS[this->items[this->items_in_bag - 1]];
}

static int _remove_item(Items *this, int item_index)
{

    int last_index = this->items_in_bag - 1;

    this->items = realloc(this->items, sizeof(int) * (this->items_in_bag - 1));
    this->item_quantities = realloc(this->items, sizeof(int) * (this->items_in_bag - 1));
    if (last_index != item_index)
    {
        for (int i = item_index; i < last_index; i++)
        {
            this->items[i] = this->items[i + 1];
            this->item_quantities[i] = this->item_quantities[i + 1];
        }
    }
    printf("\nRemoving %s at %d but from last index of %d", ITEMS[this->items[last_index]], item_index, last_index);
    this->items = realloc(this->items, sizeof(int) * (this->items_in_bag - 1));
    this->item_quantities = realloc(this->items, sizeof(int) * (this->items_in_bag - 1));
    this->items_in_bag = last_index;
    return -1;
}
static int _decrement_item(Items *this, ITEM_ENUM item_enum)
{

    int item_index, item_was_removed;

    item_was_removed = 0;
    item_index = this->find_item(this, item_enum);
    if (item_index < 0)
    {
        printf("\nThe item was not decremented");
    }
    else
    {
        if (this->item_quantities[item_index] == 1)
        {
            this->item_quantities[item_index]--;
            this->remove_item(this, item_index);
            item_was_removed = -1;
        }
        else
        {
            this->item_quantities[item_index]--;
        }
    }
    return item_was_removed;
}

static int _find_item(Items *this, ITEM_ENUM item_enum)
{
    int i, item_index;
    item_index = -1;

    for (i = 0; i < this->items_in_bag; i++)
    {
        if (this->items[i] == item_enum)
        {
            item_index = i;
        }
    }
    return item_index;
}

static int _quaff_item(Items *this, Affect *affect)
{
    int item_was_quaffed, item_was_removed;

    item_was_quaffed = 0;
    item_was_removed = 0;
    this->affect = affect;

    if (0 != ((item_was_quaffed) = (this->affect->cause_affect(affect))))
    {
        item_was_removed = this->decrement_item(this, this->affect->affect_enum);
    }
    this->affect->destroy(this->affect);
    refresh_inputs(USER_INPUTS, 6, 1);
    return item_was_removed;
}

/************************************************
 * Check if the item already exits in this bag.
 * If not call add_item.
 * Otherwise increment the existing item.
 * Return the name of the item added as a char *.
*/
static char *_loot(Items *this, ITEM_ENUM item_enum)
{
    int item_index;

    item_index = this->find_item(this, item_enum);

    if (item_index == -1)
    {
        return this->add_item(this, item_enum);
    }
    else
    {
        this->item_quantities[item_index]++;
        printf("\nYour \"%s\" has increased from %d to %d.", ITEMS[this->items[item_index]], this->item_quantities[item_index] - 1, this->item_quantities[item_index]);
        return ITEMS[this->items[item_index]];
    }
}

Items *CREATE_BAG()
{
    Items *this = (Items *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->fill_bag = _fill_bag;
    this->add_item = _add_item;
    this->find_item = _find_item;
    this->decrement_item = _decrement_item;
    this->quaff_item = _quaff_item;
    this->remove_item = _remove_item;
    this->loot = _loot;

    this->item_quantities = NULL;
    this->items = NULL;
    this->items_in_bag = 0;
    this->affect = NULL;

    return this;
}
