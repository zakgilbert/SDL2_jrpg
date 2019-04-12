#ifndef JRPG_TIME_H
#define JRPG_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

#include "Header.h"

void set_up_timer(int fps);
void start_timer();
void reset_timer();
void delay();
void print_time_delay();
int check_delta();
void update_delta();

#endif