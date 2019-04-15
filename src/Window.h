
#ifndef JRPG_WINDOW_H
#define JRPG_WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Text.h"
typedef struct _Window
{
    void (*destroy)(struct _Window *);
    void (*create_borders)(struct _Window *, int, struct SDL_Rect *);
    void (*render)(struct _Window *, struct SDL_Renderer *);
    void (*render_color_bar)(struct _Window *this, struct SDL_Renderer *renderer);
    int (*adjust_menu_colors)(struct _Window *);
    void (*render_time_bar)(struct _Window *, struct SDL_Renderer *);
    int (*timer_is_maxed)(struct _Window *);

    struct SDL_Rect border_1;
    struct SDL_Rect border_2;
    struct SDL_Rect border_3;
    struct SDL_Rect border_4;

    struct SDL_Rect rect;
    int original_width;
    int color_value;
    struct SDL_Color color_bar_color;
    int seconds_passed;
    int now;
    int before;

} Window;

Window *CREATE_WINDOW(int x, int y, int w, int h);
Window *BATTLE_PRIMARY();
Window *BATTLE_MAGIC();

void render_window(void *obj, struct SDL_Renderer *renderer);
void render_window_color_bar(void *obj, struct SDL_Renderer *renderer);
#endif
