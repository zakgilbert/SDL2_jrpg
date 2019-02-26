//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_MAIN_H
#define JRPG_MAIN_H

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

#include "Window_and_Renderer.h"
#include "Floor.h"
#include "Hero.h"
#include "Forest.h"
#include "Player_Input.h"
#include "header.h"
#include "Movement.h"
#include "Window.h"
#include "Menu.h"
#include "Hand.h"
#include "Character.h"

int quit();
void set_up_timer();
void start_timer();
void reset_timer();
void delay();
void print_time_delay();
int check_delta();
void update_delta();
int render_thread(void *);
int set_item_quanities();

#endif //JRPG_MAIN_H
