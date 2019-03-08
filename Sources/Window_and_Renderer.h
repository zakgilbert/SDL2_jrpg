//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_WINDOW_AND_RENDERER_H
#define JRPG_WINDOW_AND_RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
SDL_Window *make_window(char *);

SDL_Renderer *make_renderer(struct SDL_Window **window);

#endif //JRPG_WINDOW_AND_RENDERER_H
