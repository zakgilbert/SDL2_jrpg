
#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Render.h"
#include "Item.h"
#include "Character.h"
#include "Words.h"
#include "H.h"
#include "Enemy.h"
#include "Hero.h"
#include "Graphics.h"
#include "Animation.h"

void SET_GLOBALS();
Item *load_bag(Item *bag, int save_state);
Enemy *load_enemy(int key, struct SDL_Renderer *renderer);
Character **load_party(int save_state, struct SDL_Renderer *renderer, Animation const *animation);
void save_bag(Item *bag, int save_state);
void save(Character **party, Item *bag, int save_state);
void create_load_info();
char **get_state_info(int save_state);
void set_fullscreen(struct SDL_Window *window, Hero *hero);
void set_animation_functions();
void set_animation_textures();
int handler_tt(void *ptr);
#endif /* ASSETS_H */
