#ifndef JRPG_GRAPHICS_H
#define JRPG_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"

SDL_Texture *create_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect *rect);

#endif