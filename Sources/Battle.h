#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Graphics.h"
#include "Floor.h"
#include "Character.h"
#include "Window.h"
#include "Hero.h"
#include "Enemy.h"
#include "Assets.h"

uint32_t transition_delay1;
int calculate_time_bar(int seconds, int width);
typedef struct _battle
{
    void (*destroy)(struct _battle *);
    void (*create_battle_textures)(struct _battle *, struct SDL_Renderer *renderer);
    void (*render)(struct _battle *, struct SDL_Renderer *renderer);
    void (*update_time_bar)(Window *time_bar, Character *character);
    void (*render_battle_menu_text)(struct _battle *, struct SDL_Renderer * renderer);
    void (*render_line)(struct _battle *, struct SDL_Renderer * renderer, const char * str, SDL_Color color);

    int num_enemies;
    char *enemy_paths;
    int area;
    int roll;
    TTF_Font *font;

    Enemy **enemies;
    struct SDL_Texture * texture;
    struct SDL_Surface * surface;
    
    struct SDL_Rect rect;
    struct SDL_Texture *back_ground;
    struct SDL_Rect bg_rect;
    struct SDL_Texture **textures_party;
    struct SDL_Rect party_rect_1;
    struct SDL_Rect party_rect_2;
    struct SDL_Rect transition;
    Window *window;
    Window **time_bars;

    Character **party;
    int num_party;

} Battle;
Battle *CREATE_BATTLE(int area, int roll, struct SDL_Renderer *renderer, Character **party, int num_party);

#endif /* BATTLE_H */
