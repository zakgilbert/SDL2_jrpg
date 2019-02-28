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
static void _fill_bag(Items *this, const char **items_from_save, int *quantities, int len)
{
    this->items = (char **)malloc(sizeof(char *) * len);
    this->item_quantities = (int *)malloc(sizeof(int) * len);
    this->items_in_bag = len;

    for(int i = 0; i < this->items_in_bag; i++)
    {
        this->items[i] = (char *)malloc(strlen(items_from_save[i]) + 1);
        strcpy(this->items[i], items_from_save[i]);
        this->item_quantities[i] = quantities[i];
        printf("\nAdded %d %s's to bag", this->item_quantities, this->items[i]);
    }
}
static void _refresh_bag(Items *this)
{
}
static void _add_item(Items *this)
{
}
Items *CREATE_BAG()
{
    Items *this = (Items *)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->fill_bag = _fill_bag;
    this->refresh_bag = _refresh_bag;
    this->add_item = _add_item;

    this->item_quantities = NULL;
    this->items = NULL;
    this->items_in_bag = 0;

    return this;
}