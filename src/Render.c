
/************************
 *  Render.c
*/

#include "Render.h"

void print_node(struct Node *targ)
{
    if (NULL == targ->obj)
    {
        printf("NULL:   ");
    }
    printf("node_ptr %p\n\n", targ);
}
static void _destroy(Render_Q *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
void free_node(struct Node *node)
{
    free(node->obj);
    node->obj = NULL;
    free(node);
    node = NULL;
}
int is_freeable(deallo_function des)
{
    if (NULL == des)
        return 0;
    return 1;
}
static void _free(Render_Q *this)
{
    struct Node *temp;
    if (NULL == this)
        return;
    while (NULL != this->front)
    {
        temp = this->pop(this);
        if (is_freeable(temp->des))
        {
            temp->des(temp->obj);
        }
        free(temp);
        temp = NULL;
    }
}
static struct Node *_new_node(void *obj, render_function target, deallo_function des)
{
    struct Node *data = malloc(sizeof(struct Node));
    data->obj = obj;
    data->funct = target;
    data->des = des;
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
    struct Node *temp;
    while (NULL != this->front)
    {
        temp = r_Q->pop(this);
        (*temp->funct)(temp->obj, renderer);
        /**
        printf("%p\n", temp);
*/
        free(temp);
        temp = NULL;
    }
    this->destroy(this);
    return CREATE_RENDER_Q();
}
static Render_Q *_clone(Render_Q *this)
{
    this->add(this, this->new_node(NULL, render_clear, NULL));
    return this;
}
static void _copy(Render_Q *this)
{
    struct Node *current;
    current = this->front;
    r_Q->add(r_Q, r_Q->new_node(NULL, render_clear, NULL));
    while (current != NULL)
    {
        r_Q->add(r_Q, r_Q->new_node(current->obj, current->funct, current->des));
        current = current->next;
    }
    r_Q->add(r_Q, r_Q->new_node(NULL, render_present, NULL));
}
Render_Q *CREATE_RENDER_Q()
{
    Render_Q *this = malloc(sizeof(*this));
    this->add = _add;
    this->destroy = _destroy;
    this->new_node = _new_node;
    this->render = _render;
    this->copy = _copy;
    this->clone = _clone;
    this->pop = _pop;
    this->free = _free;
    this->size = 0;
    this->rendering = 0;
    this->front = NULL;
    this->rear = NULL;
    return this;
}
void render_clear(void *obj, struct SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
}
void render_present(void *obj, struct SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}
Render_Q *ENQUEUE(Render_Q *q, void *obj, render_function target, deallo_function des)
{
    q->add(q, q->new_node(obj, target, des));
    return q;
}
int free_handler(void *ptr)
{
    Render_Q *this = (Render_Q *)ptr;
    this->free(this);
    return 1;
}