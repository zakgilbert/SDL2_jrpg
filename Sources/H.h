
#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STRING_LIST
{
    char **list;
    int num_items;
} LIST_STRING;

LIST_STRING *CREATE_LIST_STRING(char **list, int num_items);

typedef struct INTEGER_LIST
{
    int **list;
    int num_items;
    int * num_ints;
} LIST_INT;

LIST_INT *CREATE_LIST_INT(int **list, int *num_ints, int num_items);
#endif /* H_H */
