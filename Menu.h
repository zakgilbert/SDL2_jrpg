//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_MENU_H
#define JRPG_MENU_H
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "header.h"
#include "Window.h"
#include "Hand.h"
#include "Items.h"
uint32_t transition_delay;
typedef struct __menu
{
    void (*destroy) (struct __menu *);

    Window *main_menu_bg;

    void (*render_main_menu) (struct __menu *, struct SDL_Renderer *, Hand *);

    int (*render_main_menu_options) (struct __menu *, struct SDL_Renderer *, int);

    void (*render_items_menu) (struct __menu *, struct SDL_Renderer *, Hand *);

    int (*render_items_menu_options) (struct __menu *, struct SDL_Renderer *, int);



    TTF_Font *font;
    struct SDL_Rect rect;
    struct SDL_Rect transition;
    struct SDL_Surface *surface;
    struct SDL_Texture *texture;
    int option_states;
} Menu;

Menu *CREATE_MENU ();

#endif //JRPG_MENU_H
