#ifndef BA_H
#define BA_H

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

typedef struct _Ba
{
    /* Deallocates battle */
    void (*destroy)(struct _Ba *this);
    void (*create_textures)(struct _Ba *, struct SDL_Renderer *renderer);
    /* Update battle logic */
    void (*update)(struct _Ba *this);

    Render_Q *q;
    Window *window;
    Window *action_window;
    Window **time_bars;
    Character **party;
    struct Texture *back_ground;
    Enemy **enemies;
    int num_enemies;
    int roll;

    int area;
    int first_render;
    SDL_Thread *free_thread;
} Ba;

Ba *CREATE_BA(int area, int roll, Character **party);
void create_battle_textures(void *obj, struct SDL_Renderer *renderer);
void render_back_ground_texture(void *obj, struct SDL_Renderer *renderer);
#endif /* BA_H */
