
#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"

typedef void render_function(void *obj, struct SDL_Renderer *renderer);
void render_buffer(struct SDL_Renderer *renderer);


struct Node
{
    render_function(*funct);
    void *obj;
    struct Node *next;
};
typedef struct _Render_Q
{
    struct _Render_Q *(*render)(struct _Render_Q *this, struct SDL_Renderer *renderer);
    void (*destroy)(struct _Render_Q *this);
    void (*add)(struct _Render_Q *this, struct Node * data);
    struct Node *(*new_node)(void *obj, render_function target);
    struct Node *(*pop)(struct _Render_Q *this);
    struct Node *front;
    struct Node *rear;
    int size;

} Render_Q;
Render_Q *CREATE_RENDER_Q();

extern Render_Q *render_q;
Render_Q *render_q;
#endif /* RENDER_H */
