#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "Text.h"
#include "Render.h"
#include "Atlas.h"
#include "Line.h"

typedef struct _Menu
{
    /* Free me */
    dealloc_obj destroy;

    /* Update Menu Logic called in main */
    void (*update_main)(struct _Menu *this);
    /* Add main menu render functions to render queue. */
    void (*set_main_menu)(struct _Menu *this);
    /* Add main menu option text to render queue. */
    int (*set_text_menu_options)(struct _Menu *this);
    /* Add Character image textures to render queue */
    void (*set_bio_image)(struct _Menu *this);

    /* Add Character status text to render queue */
    void (*set_text_stats)(struct _Menu *this);

    /* Update items menu logic, called in main */
    void (*update_items_menu)(struct _Menu *this);
    /* Add items menu render functions to render queue */
    int (*set_items_menu)(struct _Menu *this);
    /* Add item text to render queue */
    int (*set_text_items_menu)(struct _Menu *this);

    /* Update use items menu logic, called in main */
    void (*update_use_item)(struct _Menu *this);
    /* Add use item text to render queue */
    void (*set_text_use_item)(struct _Menu *this);
    int item_in_use;
    int previous_number_states;
    Window *back_ground_use_item;

    /* Update use config menu logic, called in main */
    void (*update_config)(struct _Menu *this);
    /* Add config render functions to render queue */
    int (*set_config)(struct _Menu *this);
    /* Add config text and color bars to render queue */
    int (*set_text_config)(struct _Menu *this);
    /* Updates the window color */
    void (*update_window_color)(Window **color_bars, int current_state);
    Window **rgb_bars;
    char rgb_matrix[3][50];

    Window *back_ground;

    Character **party;
    Hand *hand;
    Item *bag;
    Render_Q *q;
    Atlas *atlas;
    int time_to_load;
    int skip;
    Uint32 delay;

} Menu;
Menu *CREATE_MENU(Character **party, Hand *hand, Item *bag, Atlas *atlas);
void menu_transition(void *obj, struct SDL_Renderer *renderer);

#endif /* MENU_H */
