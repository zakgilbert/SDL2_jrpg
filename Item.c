#include "Item.h"

static void _destroy(Items *this)
{
    if (NULL != this->items)
    {
        free(this->items);
    }
    if (NULL != this->item_quantities)
    {
        free(this->item_quantities);
    }
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _fill_bag(Items *this, const char items_from_save[3][10], int quantities[3], int len)
{
    this->items = (char **)malloc(sizeof(char *) * len);
    this->item_quantities = (int *)malloc(sizeof(int) * len);
    this->items_in_bag = len;
    printf("\nLen %d\nItems in bag %d", len, this->items_in_bag);
    for (int i = 0; i < this->items_in_bag; i++)
    {
        this->items[i] = (char *)malloc(strlen(items_from_save[i]) + 1);
        strcpy(this->items[i], items_from_save[i]);
        this->item_quantities[i] = quantities[i];
        printf("\nAdded %d %s's to bag at i = %d", this->item_quantities[i], this->items[i], i);
    }
}
static void _add_item(Items *this, ITEM_ENUM item_enum)
{

    size_t new_items_size = (sizeof(char *) * (this->items_in_bag + 1));
    size_t new_quantities_size = (sizeof(int) * (this->items_in_bag + 1));

    this->items = realloc(this->items, new_items_size);
    this->items[this->items_in_bag] = (char *)malloc(strlen(ITEMS[item_enum]) + 1);
    strcpy(this->items[this->items_in_bag], ITEMS[item_enum]);
    this->item_quantities = realloc(this->item_quantities, new_quantities_size);
    this->item_quantities[this->items_in_bag] = 1;
    this->items_in_bag++;
}

static int _remove_item(Items *this, int item_index)
{
    int last_index = this->items_in_bag - 1;
    if (last_index != item_index)
    {
        char *temp = (char *)malloc(strlen(this->items[last_index]) + 1);
        strcpy(temp, this->items[last_index]);
        this->items[last_index] = realloc(this->items[last_index], strlen(this->items[item_index]) + 1);
        strcpy(this->items[last_index], this->items[item_index]);
        this->items[item_index] = realloc(this->items[item_index], strlen(temp) + 1);
        strcpy(this->items[item_index], temp);

        free(temp);
        temp = NULL;
        int int_temp = this->item_quantities[last_index];
        this->item_quantities[last_index] = this->item_quantities[item_index];
        this->item_quantities[item_index] = int_temp;
    }
    printf("\nRemoving %s at %d but from last index of %d", this->items[last_index], item_index, last_index);
    free(this->items[last_index]);
    this->items[last_index] = NULL;
    this->items = realloc(this->items, sizeof(char *) * (this->items_in_bag - 1));
    this->item_quantities = realloc(this->item_quantities, sizeof(int) * (this->items_in_bag - 1));
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

static ITEM_ENUM _get_enum(Items *this, int item_index)
{

    int i, enum_value;
    enum_value = 0;
    for (i = 0; i < ITEM_QUANTITY; i++)
    {
        if (strcmp(this->items[item_index], ITEMS[i]) == 0)
        {
          //  printf("\nFound a match at in index %d in bag and index %d in Items", item_index, i);
           // printf("\nThe match is %s and %s", this->items[item_index], ITEMS[i]);
            enum_value = i;
        }
    }
    return enum_value;
}
static int _find_item(Items *this, ITEM_ENUM item_enum)
{
    int i, item_index;
    item_index = -1;

    for (i = 0; i < this->items_in_bag; i++)
    {
        if (strcmp(this->items[i], ITEMS[item_enum]) == 0)
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

    if (item_was_quaffed = this->affect->cause_affect(affect))
    {
        item_was_removed = this->decrement_item(this, this->affect->affect_enum);
    }
    this->affect->destroy(this->affect);
    refresh_inputs(inputs, 6, 1);
    return item_was_removed;
}

static void _loot(Items *this, ITEM_ENUM item_enum)
{
    int item_index;

    item_index = this->find_item(this, item_enum);

    if (item_index == -1)
    {
        this->add_item(this, item_enum);
    }
    else
    {
        this->item_quantities[item_index]++;
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
    this->get_enum = _get_enum;

    this->item_quantities = NULL;
    this->items = NULL;
    this->items_in_bag = 0;
    this->affect = NULL;

    return this;
}