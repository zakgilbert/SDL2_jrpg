#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"
#include "Graphics.h"
#include "Floor.h"
#include "Character.h"
#include "Window.h"
#include "Hero.h"
#include "Enemy.h"
#include "Assets.h"
#include "Hand.h"
#include "Words.h"
#include "Battle_Q.h"
#include "Render.h"
#include "Atlas.h"
#include "Line.h"
#include "Time.h"
#include "Hand.h"

typedef struct _Battle
{
    /* Deallocates battle */
    void (*destroy)(struct _Battle *this);
    void (*create_textures)(struct _Battle *, struct SDL_Renderer *renderer);
    /* Update battle logic */
    void (*update)(struct _Battle *this);
    int (*set_text_stats)(struct _Battle *this);
    int (*set_text_enemies)(struct _Battle *this);
    Uint32 (*hero_callback)(Uint32 interval, void *param);

    Render_Q *q;
    Battle_Q *b;
    Window *window;
    Window *action_window;
    Window **time_bars;
    Character **party;
    Atlas *atlas;
    Hand *hand;
    struct Texture *back_ground;
    Enemy **enemies;
    int num_enemies;
    int index;
    int roll;
    int area;
    int first_render;
    SDL_Thread *free_thread;
    SDL_TimerID *hero_timers;
    struct timer_packet **timer_packets;
} Battle;
struct timer_packet
{
    Character *c;
    Battle *ba;
};

Battle *CREATE_BATTLE(int area, int roll, Character **party, Atlas *atlas, Hand *hand);
void create_battle_textures(void *obj, struct SDL_Renderer *renderer);
void render_back_ground_texture(void *obj, struct SDL_Renderer *renderer);

#endif /* BATTLE_H */
