
#ifndef BATTLE_Q_H
#define BATTLE_Q_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Window.h"
#include "Atlas.h"
#include "Render.h"
#include "Line.h"
#include "Character.h"

struct node
{
    Character *hero;
    struct node *next;
};
typedef struct _Battle_Q
{
    void (*destroy)(struct _Battle_Q *this);
    void (*add)(struct _Battle_Q *this, Character *hero);
    Character *(*peek)(struct _Battle_Q *this, Atlas *at, Render_Q *q);
    void (*re_q)(struct _Battle_Q *this, struct node *ode);
    void (*print_q)(struct _Battle_Q *this);
    struct node *(*new_node)(struct _Battle_Q *this, Character *hero);
    struct node *(*pop)(struct _Battle_Q *this);
    struct node *front;
    struct node *rear;
    int size;
} Battle_Q;
Battle_Q *CREATE_BATTLE_Q();
#endif /* BATTLE_Q_H */
