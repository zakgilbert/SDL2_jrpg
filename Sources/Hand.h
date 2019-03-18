//
// Created by zachary on 1/27/19.
//

#ifndef JRPG_HAND_H
#define JRPG_HAND_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"

int animate_hand_thread(void *);

typedef struct _hand
{
    void (*destroy) (struct _hand *);

    void (*render) (struct _hand *, struct SDL_Renderer *);

    void (*create_texture) (struct _hand *, char *, struct SDL_Renderer *, int, int);

    void (*animate) (struct _hand *);

    void (*main_menu_position) (struct _hand*);
    
    void (*items_menu_position) (struct _hand*);
    
    void (*config_menu_position) (struct _hand*);

    void (*use_item_position) (struct _hand*);

    void (*vertical_horizontal) (struct _hand *);

    void (*set_states) (struct _hand*, int, int, int, int, int, int, int, int);


    int state_0[2];
    int state_1[2];
    int state_2[2];
    int state_3[2];
    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    struct SDL_Rect position;
    int current_state;
    int number_of_states;

    struct SDL_Rect *(*get_rect_pointer) (struct _hand *);

    struct SDL_Rect *(*get_rect_pos_pointer) (struct _hand *);

    int (*change_state_quantity) (struct _hand *, int number, int add);

    int (*change_get_state) (struct _hand *, int number, int add);

    int (*move_horizontal) (struct _hand *, int);

    int (*move_vertical) (struct _hand *, int);

} Hand;

Hand *CREATE_HAND ();

#endif //JRPG_HAND_H
