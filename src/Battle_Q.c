
/************************
 *  Battle_Q.c
*/

#include "Battle_Q.h"

static void _destroy(Battle_Q *this)
{
    struct node *temp;
    if (NULL != this)
    {
        while (NULL != this->front)
        {
            temp = this->pop(this);
            temp->hero->current_state = 0;
            free(temp);
            temp = NULL;
        }
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
            current = current->next;
        }
    }
}

static struct node *_new_node(Battle_Q *this, Character *hero)
{
    struct node *data = malloc(sizeof(struct node));
    data->hero = hero;
    data->next = NULL;
    return data;
}

static Character *_peek(struct _Battle_Q *this, Atlas *at, Render_Q *q)
{
    if (NULL != this->front)
        return this->front->hero;
    return NULL;
}
static void _add(Battle_Q *this, Character *hero)
{
    struct node *data = this->new_node(this, hero);
    data->hero->current_state = primary;
    this->size++;
    printf("addiing character: %s to the battle_q\n", hero->name);
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
    struct node *temp;
    if (NULL == this->front)
    {
        return NULL;
    }
    temp = this->front;
    this->front = this->front->next;
    if (NULL == this->front)
    {
        this->rear = NULL;
    }
    temp->hero->current_state = waiting;
    return temp;
}
static void _re_q(Battle_Q *this, struct node *ode)
{
    struct node *data;
    data = ode;
    if (NULL == this->rear)
    {
        this->front = data;
        this->rear = data;
        return;
    }
    this->rear->next = data;
    this->rear = data;
    data->hero->current_state = primary;
}

Battle_Q *CREATE_BATTLE_Q()
{
    Battle_Q *this = malloc(sizeof(*this));
    this->add = _add;
    this->pop = _pop;
    this->print_q = _print_q;
    this->destroy = _destroy;
    this->new_node = _new_node;
    this->peek = _peek;
    this->re_q = _re_q;
    this->front = NULL;
    this->rear = NULL;
    this->size = 0;

    return this;
}