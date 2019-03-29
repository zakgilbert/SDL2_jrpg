
/************************
 *  Battle_Q.c
*/

#include "Battle_Q.h"

/*
typedef struct _Battle_Q
{
    void (*destroy)(struct _Battle_Q *this);
    struct node
    {
        int key;
        int type;
        int index;
        struct node *prev;
    };
    struct node *front;
    struct node *rear;
} Battle_Q;
Battle_Q *CREATE_BATTLE_Q(int size);
*/
static void _destroy(Battle_Q *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _print_q(Battle_Q *this)
{
    struct node *current;
    if (NULL == this->front)
    {
        printf("q is empty\n");
    }
    else
    {
        current = this->front;
        while (NULL != current->next)
        {

            printf("key: %d  index: %d  type:  %d\n", current->key, current->index, current->type);
            current = current->next;
        }
    }
}

static struct node *_new_node(Battle_Q *this, int key, int type, int index)
{
    struct node *data = malloc(sizeof(struct node));
    data->key = key;
    data->type = type;
    data->index = index;
    data->next = NULL;
    return data;
}

static void _add(Battle_Q *this, int key, int type, int index)
{
    struct node *data = this->new_node(this, key, type, index);

    if (NULL == this->rear)
    {
        this->front = data;
        this->rear = data;
        return;
    }
    this->rear->next = data;
    this->rear = data;
}
static struct node *_pop(Battle_Q *this)
{
    if (NULL == this->front)
    {
        return NULL;
    }
    struct node *temp = this->front;
    this->front = this->front->next;
    if (NULL == this->front)
    {
        this->rear = NULL;
    }
    return temp;
}
static void _re_q(Battle_Q *this, struct node *ode)
{
    struct node *data = ode;
    if (NULL == this->rear)
    {
        this->front = data;
        this->rear = data;
        return;
    }
    this->rear->next = data;
    this->rear = data;
}

Battle_Q *CREATE_BATTLE_Q()
{
    Battle_Q *this = malloc(sizeof(*this));
    this->add = _add;
    this->pop = _pop;
    this->print_q = _print_q;
    this->destroy = _destroy;
    this->new_node = _new_node;
    this->re_q = _re_q;
    this->front = NULL;
    this->rear = NULL;

    return this;
}