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
#include "Words.h"
#include "Character.h"

uint32_t transition_delay;

typedef struct __menu
{
    void (*destroy)(struct __menu *);

    Window *main_menu_bg;

    Window *select_character_bg;

    void (*render_character_main_menu_bio) (struct __menu *, struct SDL_Renderer *, Hand *); 

    void (*render_character_main_menu_image)(struct __menu *, struct SDL_Renderer *, Hand *,Character **);  

    void (*render_main_menu)(struct __menu *, struct SDL_Renderer *, Hand *, Character ** );

    int (*render_main_menu_options)(struct __menu *, struct SDL_Renderer *, int);

    void (*render_items_menu)(struct __menu *, struct SDL_Renderer *, Hand *);

    int (*render_items_menu_options)(struct __menu *, struct SDL_Renderer *, int);

    void (*render_use_item_menu)(struct __menu *, struct SDL_Renderer *, Hand *);

    int (*render_use_item_menu_options)(struct __menu *, struct SDL_Renderer*, int);

    TTF_Font *font;
    struct SDL_Rect rect;
    struct SDL_Rect transition;
    struct SDL_Surface *surface;
    struct SDL_Texture *texture;
    int option_states;
    int item_being_used;
} Menu;

Menu *CREATE_MENU();

#endif //JRPG_MENU_H
