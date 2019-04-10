
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
#include "Text.h"
#include "Render.h"

uint32_t transition_delay;
void render_line(TTF_Font, char *str);
typedef struct _Menu
{
    void (*destroy)(struct _Menu *);
    void (*render_line)(struct _Menu *, struct SDL_Renderer *renderer, const char *str, SDL_Color color);

    /**
 * MAIN MENU
 */
    void (*update_main_menu)(struct _Menu *this);
    void (*set_q_main_menu)(struct _Menu *this);
    int (*set_main_menu_text_options)(struct _Menu *this, int _x, int _y, int size, int num_options);
    void (*set_character_main_menu_image)(struct _Menu *this);
    void (*set_stat_text)(struct _Menu *this, int _x, int _y, int size, int key);

    /**
 * ITEMS MENU
 */
    void (*update_items_menu)(struct _Menu *this);
    void (*set_q_items_menu)(struct _Menu *this);
    int (*set_items_menu_options)(struct _Menu *);

    /**
 * USE_ITEMS
 */
    void (*update_use_items_menu)(struct _Menu *this);

    /**
 * CONFIG
 */
    void (*update_config)(struct _Menu *this);
    void (*set_q_config)(struct _Menu *this);
    int (*set_config_menu_options)(struct _Menu *);
    void (*change_window_color)(Window **color_bars, int current_state);

    void (*update)(struct _Menu *this);
    void (*set_q)(struct _Menu *this);

    Window *main_menu_bg;

    Window *select_character_bg;

    Window **load_save_bg;
    Window **rgb_bars;

    void (*render_main_menu)(struct _Menu *, struct SDL_Renderer *, Hand *, Character **);

    /**
    
        void (*render_character_stats)(struct _Menu *, struct SDL_Renderer *,
                                       Hand *, Character **party, int, int,
                                       int, int);
    
    
    
        void (*render_items_menu)(struct _Menu *, struct SDL_Renderer *, Hand *, Item *);
    
    
        void (*render_use_item_menu)(struct _Menu *, struct SDL_Renderer *, Hand *, Character **, Item *);
    
        void (*render_config_menu)(struct _Menu *, struct SDL_Renderer *);
    
    
    
        void (*render_save_menu)(struct _Menu *, struct SDL_Renderer *);
    
        int (*render_save_menu_options)(struct _Menu *, struct SDL_Renderer *);
*/

    TTF_Font *font;
    struct SDL_Rect rect;
    struct SDL_Rect transition;
    struct SDL_Surface *surface;
    struct SDL_Texture *texture;
    int option_states;
    int item_being_used;
    int previous_number_of_states;
    int first_load;
    int skip;
    Render_Q *q;
    Uint32 delay;
    Character **party;
    Item *bag;
    Hand *hand;
    char rgb_matrix[3][50];
} Menu;

Menu *CREATE_MENU(Character **party, Hand *hand, Item *bag);
void render_transition(void *obj, struct SDL_Renderer *renderer);
#endif
