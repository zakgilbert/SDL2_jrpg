//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_PLAYER_INPUT_H
#define JRPG_PLAYER_INPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "header.h"

int input_thread (void *data);
void get_player_input();
int wait_for_okay();
#endif //JRPG_PLAYER_INPUT_H
