
/************************
 *  Assets.c
*/

#include "Assets.h"


static const char *ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)};

Items * load_bag(Items * bag, int save_state)
{
    FILE * in;
    int num_items;
    int * items;
    int * item_quantities;

    num_items = 0;
    items = NULL;
    item_quantities = NULL;

    in = fopen("data/bag.txt", "r");

    fscanf(in, "%d", &num_items);

    items = malloc(sizeof(int) * num_items);
    item_quantities = malloc(sizeof(int) * num_items);

    for(size_t i = 0; i < num_items; i++)
    {
        fscanf(in, "%d", &item_quantities[i]);
    }
    for(size_t k = 0; k < num_items; k++)
    {
        fscanf(in, "%d", &items[k]);
    }
    fclose(in);
    bag->items = items;
    bag->item_quantities = item_quantities;
    bag->items_in_bag = num_items;
    return bag;
}

void * save_bag(Items * bag, int save_state)
{
    FILE * out;

    out = fopen("data/bag.txt", "w");

    fprintf(out, "%d\n", bag->items_in_bag);
    
    for(size_t i = 0; i < bag->items_in_bag - 1; i++)
    {
        fprintf(out, "%d ", bag->item_quantities[i]);
    }
    fprintf(out, "%d\n", bag->item_quantities[bag->items_in_bag - 1]);
    for(size_t i = 0; i < bag->items_in_bag - 1; i++)
    {
        fprintf(out, "%d ", bag->items[i]);
    }
    fprintf(out, "%d\n", bag->items[bag->items_in_bag - 1]);
    
}