//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_MENU_H
#define JRPG_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Affect.h"
#include "Item.h"
#include "Header.h"
#include "Window.h"
#include "Hand.h"
#include "Character.h"
#include "Words.h"

uint32_t transition_delay;

typedef struct _menu
{
    void (*destroy)(struct _menu *);

    Window *main_menu_bg;

    Window *select_character_bg;

    Window **load_save_bg;

    void (*render_character_stats)(struct _menu *, struct SDL_Renderer *, Hand *, int, int, int, int);

    void (*render_character_main_menu_image)(struct _menu *, struct SDL_Renderer *, Hand *, Character **);

    void (*render_main_menu)(struct _menu *, struct SDL_Renderer *, Hand *, Character **);

    int (*render_main_menu_options)(struct _menu *, struct SDL_Renderer *, int);

    void (*render_items_menu)(struct _menu *, struct SDL_Renderer *, Hand *, Item *);

    int (*render_items_menu_options)(struct _menu *, struct SDL_Renderer *, Item *, int);

    void (*render_use_item_menu)(struct _menu *, struct SDL_Renderer *, Hand *, Character **, Item *);

    void (*render_config_menu)(struct _menu *, struct SDL_Renderer *, Hand *);

    int (*render_config_menu_options)(struct _menu *, struct SDL_Renderer *, Hand *, int);
    
    void (*change_window_color)(Window ** color_bars, int current_state);
    
    void (*render_save_menu)(struct _menu *, struct SDL_Renderer *, Hand *);

    int (*render_save_menu_options)(struct _menu *, struct SDL_Renderer *, Hand *, int);

    TTF_Font *font;
    struct SDL_Rect rect;
    struct SDL_Rect transition;
    struct SDL_Surface *surface;
    struct SDL_Texture *texture;
    int option_states;
    int item_being_used;
    int previous_number_of_states;
} Menu;

Menu *CREATE_MENU();

#endif //JRPG_MENU_H
