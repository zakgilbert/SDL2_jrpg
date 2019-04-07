
#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Item.h"
#include "Character.h"
#include "Words.h"
#include "H.h"
#include "Enemy.h"
#include "Hero.h"
#include "Render.h"
void SET_GLOBALS();
Item *load_bag(Item *bag, int save_state);
Enemy *load_enemy(int key, struct SDL_Renderer * renderer);
Character **load_party(int save_state, struct SDL_Renderer *renderer);

void save_bag(Item *bag, int save_state);
void save(Character **party, Item *bag, int save_state);
void create_load_info();
char **get_state_info(int save_state);
void set_fullscreen(struct SDL_Window * window, Hero * hero);

#endif /* ASSETS_H */
