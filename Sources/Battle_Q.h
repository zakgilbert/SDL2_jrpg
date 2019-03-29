
#ifndef BATTLE_Q_H
#define BATTLE_Q_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

struct node
{
    int key;
    int type;
    int index;
    struct node *next;
};
typedef struct _Battle_Q
{
    void (*destroy)(struct _Battle_Q *this);
    void (*add)(struct _Battle_Q *this, int key, int type, int index);
    void (*print_q)(struct _Battle_Q *this);
    struct node *(*new_node)(struct _Battle_Q *this, int key, int type, int index);
    struct node *(*pop)(struct _Battle_Q *this);
    struct node *front;
    struct node *rear;
} Battle_Q;
Battle_Q *CREATE_BATTLE_Q();
#endif /* BATTLE_Q_H */
