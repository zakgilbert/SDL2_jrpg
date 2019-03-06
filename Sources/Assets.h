#ifndef JRPG_ASSETS_H
#define JRPG_ASSETS_H

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
#include <SDL2/SDL_platform.h>
#include "header.h"

int inputs[6];
int NUM_CHARACTERS;
int EDGE_DETECTION[4];
int READY_TO_INTERACT;
int MOVEMENT_DISABLED;
int ITEM_QUANTITY;
int IS_MOVING;
int REFRESH_ITEMS;
int NUM_STATS;
int X;
int Y;
int MAP_WIDTH;
int MAP_HEIGHT;
int WAITING_FOR_MESSAGE;
char **STAT_MATRIX;

struct SDL_Color WHITE;
struct SDL_Color GREY;
struct SDL_Color MENU_BACKGROUND;
struct SDL_Color RED;
struct SDL_Color BLU;
struct SDL_Color GRN;

struct MY_GLOBAL_LIBRARY G;
void CREATE_GLOBALS();

#endif