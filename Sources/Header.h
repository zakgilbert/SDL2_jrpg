//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_HEADER_H
#define JRPG_HEADER_H

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
#include <stdint.h>
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)
extern int FPS;
extern int FRAMES_RENDERED;

extern int NUM_STATS;
extern int NUM_AREAS;
extern char **STAT_MATRIX;
extern int NUM_CHARACTERS;
extern int ITEMS_IN_BAG;
extern int READY_TO_INTERACT;
extern int *ITEM_QUANTITIES;
extern char **BAG;
extern int *BAG_QUANTITIES;
extern int USER_INPUTS[6];
extern int EDGE_DETECTION[4];
extern int AT_COLLIDABLE_EDGE[4];
extern int MOVEMENT_DISABLED;
extern int IS_MOVING;
extern int X;
extern int Y;
extern int TICK;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int REFRESH_ITEMS;
extern int HERO_WIDTH;
extern int HERO_HEIGHT;

extern int WAITING_FOR_MESSAGE;
extern struct SDL_Color WHITE;
extern struct SDL_Color GREY;
extern struct SDL_Color GREY;
extern struct SDL_Color MENU_BACKGROUND;
extern struct SDL_Color RED;
extern struct SDL_Color BLU;
extern struct SDL_Color GRN;

enum states
{
    DARK_FOREST,
    MAIN_MENU,
    ITEMS_MENU,
    USE_ITEM,
    MESSAGE,
    CONFIG
};
enum states state, previous_state;
enum INPUTS
{
    NONE,
    OKAY,
    QUIT,
    CANCEL
};
enum INPUTS INPUT;

enum COLLIDABLE_TYPES
{
    CHEST,
    NPC,
    ENEMY,
    BUTTON
};

enum BUTTON
{
    ON,
    OFF
};

enum BUTTON INTERACT;

int FPS;
int FRAMES_RENDERED;

int USER_INPUTS[6];
int NUM_CHARACTERS;
int EDGE_DETECTION[4];
int READY_TO_INTERACT;
int AT_COLLIDABLE_EDGE[4];
int MOVEMENT_DISABLED;
int ITEM_QUANTITY;
int IS_MOVING;
int REFRESH_ITEMS;
int HERO_WIDTH;
int HERO_HEIGHT;

int NUM_STATS;
int NUM_AREAS;
int X;
int Y;
int TICK;
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

int refresh_inputs(int *, int, int);
void set_items(int *);
int quit();
int render_thread(void *);
void SET_GLOBALS();
#endif //JRPG_HEADER_H