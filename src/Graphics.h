#ifndef JRPG_GRAPHICS_H
#define JRPG_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
struct Texture
{
    struct SDL_Texture *t;
    struct SDL_Rect r;
};

SDL_Window *make_window(char *);
SDL_Renderer *make_renderer(struct SDL_Window **window);
SDL_Texture *create_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect *rect);
Rect * set_rect(Rect * rect, int x, int y, int w, int h);

#endif