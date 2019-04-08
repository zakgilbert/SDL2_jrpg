
/************************
 *  Render.c
*/

#include "Render.h"

static void _destroy(Render_Q *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static struct Node *_new_node(void *obj, render_function target)
{
    struct Node *data = malloc(sizeof(struct Node));
    data->obj = obj;
    data->funct = target;
    data->next = NULL;
    return data;
}
static void _add(Render_Q *this, struct Node *data)
{
    if (NULL == this->rear)
    {
        this->front = data;
        this->rear = data;
        return;
    }
    this->rear->next = data;
    this->rear = data;
}
static struct Node *_pop(Render_Q *this)
{
    struct Node *temp;
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
    return temp;
}
Render_Q *_render(Render_Q *this, struct SDL_Renderer *renderer)
{
    Render_Q *new_q = CREATE_RENDER_Q();
    struct Node *temp;
    while (NULL != this->front)
    {
        temp = this->pop(this);
        (*temp->funct)(temp->obj, renderer);
        new_q->add(new_q, temp);
    }
    return new_q;
}
Render_Q *CREATE_RENDER_Q()
{
    Render_Q *this = malloc(sizeof(*this));
    this->add = _add;
    this->destroy = _destroy;
    this->new_node = _new_node;
    this->render = _render;
    this->pop = _pop;
    this->size = 0;

    this->front = NULL;
    this->rear = NULL;
    return this;
}