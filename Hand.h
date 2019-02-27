//
// Created by zachary on 1/27/19.
//

#ifndef JRPG_HAND_H
#define JRPG_HAND_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "header.h"

int animate_hand_thread(void *);

typedef struct __hand
{
    void (*destroy) (struct __hand *);

    void (*render) (struct __hand *, struct SDL_Renderer *);

    void (*create_texture) (struct __hand *, char *, struct SDL_Renderer *, int, int);

    void (*animate) (struct __hand *);

    void (*main_menu_position) (struct __hand*);
    
    void (*items_menu_position) (struct __hand*);

    void (*use_item_position) (struct __hand*);

    int (*vertical_horizontal) (struct __hand *);

    void (*set_states) (struct __hand*, int, int, int, int, int, int, int, int);


    int state_0[2];
    int state_1[2];
    int state_2[2];
    int state_3[2];
    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    struct SDL_Rect position;
    int current_state;
    int number_of_states;

    struct SDL_Rect *(*get_rect_pointer) (struct __hand *);

    struct SDL_Rect *(*get_rect_pos_pointer) (struct __hand *);

    int (*change_state_quantity) (struct __hand *, int number, int add);

    int (*change_get_state) (struct __hand *, int number, int add);

    int (*move_horizontal) (struct __hand *, int);

    int (*move_vertical) (struct __hand *, int);

} Hand;

Hand *CREATE_HAND ();

#endif //JRPG_HAND_H
