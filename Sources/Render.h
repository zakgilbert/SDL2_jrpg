
#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Floor.h"
#include "Hero.h"
#include "Area.h"

render_function *add_target(Target this, render_function *function_t);
void add_target_function(render_function *target_function);
void render_buffer(struct SDL_Renderer *renderer);
void render_forest_floor(void *obj, struct SDL_Renderer *renderer);
void render_forest_trees(void *obj, struct SDL_Renderer *renderer);

void render_hero(void *obj, struct SDL_Renderer *renderer);

#endif /* RENDER_H */
