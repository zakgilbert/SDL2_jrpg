
/************************
 *  H.c
*/

#include "H.h"

LIST_STRING *CREATE_LIST_STRING(char **list, int num_items)
{
    int i;
    LIST_STRING *this = malloc(sizeof(*this));

    this->list = malloc(sizeof(char *) * num_items);
    for (i = 0; i < num_items; i++)
    {
        this->list[i] = malloc(strlen(list[i]));
        this->list[i] = list[i];
    }
    this->num_items = num_items;
    return this;
}

LIST_INT *CREATE_LIST_INT(int **list, int * num_ints, int num_items)
{
    int i, k;

    LIST_INT *this = malloc(sizeof(*this));

    this->list = malloc(sizeof(int *) * num_items);
    this->num_ints = malloc(sizeof(int) * num_items);
    for (i = 0; i < num_items; i++)
    {
        this->list[i] = malloc(sizeof(int) * num_ints[i]);
        this->num_ints[i] = num_ints[i];
        for (k = 0; k < num_ints[i]; k++)
        {
            this->list[i][k] = list[i][k];
        }
    }
    this->num_items = num_items;
    return this;
}