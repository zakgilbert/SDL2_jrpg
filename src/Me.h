#ifndef ME_H
#define ME_H

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

typedef struct _Me
{
    /* Free me */
    dealloc_obj destroy;

    /* Update Me Logic called in main */
    void (*update_me)(struct _Me *this);
    /* Add main menu render functions to render queue. */
    void (*set_main_menu)(struct _Me *this);
    /* Add main menu option text to render queue. */
    int (*set_text_menu_options)(struct _Me *this);
    /* Add Character image textures to render queue */
    void (*set_bio_image)(struct _Me *this);

    /* Add Character status text to render queue */
    void (*set_text_stats)(struct _Me *this);

    /* Update items menu logic, called in main */
    void (*update_items_menu)(struct _Me *this);
    /* Add items menu render functions to render queue */
    void (*set_items_menu)(struct _Me *this);
    /* Add item text to render queue */
    int (*set_text_items_menu)(struct _Me *this);

    Window *back_ground;
    Character **party;
    Hand *hand;
    Item *bag;
    Render_Q *q;
    Atlas *atlas;
    int time_to_load;
    int skip;
    Uint32 delay;

} Me;
Me *CREATE_ME(Character **party, Hand *hand, Item *bag, Atlas *atlas);
void menu_transition(void *obj, struct SDL_Renderer *renderer);

#endif /* ME_H */
