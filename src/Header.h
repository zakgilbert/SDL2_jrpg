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
#include "H.h"
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)
#define SPRITE_FRAME_WIDTH (32)
#define SPRITE_FRAME_HEIGHT (32)
#define PRIME_1 (163)
#define PRIME_2 (151)
#define NUM_ANI (13)

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
extern int EDGE_DETECTION[4];
extern int AT_COLLIDABLE_EDGE[4];
extern int MOVEMENT_DISABLED;
extern int IS_MOVING;
extern int X;
extern int Y;
extern int TICK;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int COLLISION_X;
extern int COLLISION_Y;
extern int REFRESH_ITEMS;
extern int HERO_WIDTH;
extern int HERO_HEIGHT;
extern int IN_BATTLE;
extern int NUM_STEPS;
extern int WAITING_FOR_MESSAGE;
extern int TICKS;
extern int GAME_SECS;
extern int ROLL;
extern int FULLSCREEN_ON;
extern int NUM_TARGETS;
extern struct SDL_Color WHITE;
extern struct SDL_Color GREY;
extern struct SDL_Color MENU_BACKGROUND;
extern struct SDL_Color GOLD;
extern struct SDL_Color RED;
extern struct SDL_Color BLU;
extern struct SDL_Color GRN;
extern struct STRING_LIST **DIALOGUES;
extern struct INTEGER_LIST **BATTLE_LINEUP;
extern struct STRING_LIST *NPC_PATHS;
extern struct STRING_LIST *ENEMY_PATHS;
extern struct STRING_LIST *BATTLE_BACKGROUNDS;
extern struct STRING_LIST *BATTLE_CHARACTER_GRAPHICS;
extern struct STRING_LIST *CHARACTER_NAMES;
extern struct STRING_LIST *CHARACTER_AGES;
extern struct STRING_LIST *CHARACTER_JOBS;
extern struct STRING_LIST *CHARACTER_BIO_PATHS;
extern struct STRING_LIST *SAVE_PATHS;
extern struct STRING_LIST **LOAD_SAVE_INFO_STRINGS;
extern struct STRING_LIST *ENEMIES;
extern struct SDL_Textures **alpha_textures;

/* Free obj */
typedef void (*dealloc_obj)(void *this);

enum KEYS
{
    S = SDL_SCANCODE_S,
    W = SDL_SCANCODE_W,
    A = SDL_SCANCODE_A,
    D = SDL_SCANCODE_D,
    J = SDL_SCANCODE_J,
    L = SDL_SCANCODE_L,
    O = SDL_SCANCODE_O,
    F = SDL_SCANCODE_F,
    NON
};
int UP();
int LEFT();
int RIGHT();
int DOWN();
int CONFIRM();
int CANCEL();
int EXIT();
int FULL();

enum KEYS KEY;
extern Uint8 *key_state;
Uint8 *key_state;
union SDL_Event ev;
typedef struct SDL_Renderer *Renderer;
typedef struct SDL_Rect Rect;
typedef struct SDL_Texture *Tex;
typedef char *GET_DATA(void *obj);
typedef void change_animation_pos(Rect *rect_1, Rect *rect_2, int *index);

/**
    enum ANIMATION_FUNCTIONS
    {
        stand,
        pray_1,
        cast,
        step,
        hit,
        defend,
        pray_2,
        cast_step,
        injured,
        dead,
        no_ani,
        execute,
        fin
    };
*/
extern change_animation_pos *animation_functions[NUM_ANI];
change_animation_pos *animation_functions[NUM_ANI];
enum battle_states
{
    waiting,
    in_timer,
    primary,
    attack,
    magic,
    item,
    casting,
};
enum states
{
    DARK_FOREST,
    MAIN_MENU,
    ITEMS_MENU,
    USE_ITEM,
    MESSAGE,
    CONFIG,
    SAVE,
    BATTLE
};
enum states state, previous_state;
enum CHARACTER_BATTLE_ANIMATION
{
    ATK,
    CST,
    NOT_ANIMATING_BATTLE_CHARACTER
};
enum CHARACTER_BATTLE_ANIMATION CURRENT_CHARACTER_BATTLE_ANIMATION;

enum CHARACTERS
{
    LOCKE,
    TERRA,
    SABIN,
    GAU
};
enum SAVE_STATES
{
    SAVE_1,
    SAVE_2,
    SAVE_3
};
enum SAVE_STATES SAVE_STATE;

enum LOAD_SAVE_INFO
{
    LEAD_CHARACTER
};

enum COLLIDABLE_TYPES
{
    CHEST,
    NPC,
    ENEMY,
    BUTTON
};

enum ENEMIES
{
    Kiros,
    Samurai
};

enum BUTTON
{
    ON,
    OFF
};

enum BUTTON INTERACT;
enum MESSAGE_TYPES
{
    ONE_LINER,
    DIALOGUE
};
enum MESSAGE_TYPES MESSAGE_TYPE;

enum BATTLE_MEMBER_TYPE
{
    PARTY_MEMBER,
    MONSTER
};

enum NPCS
{
    GIGAS,
    SASH
};

enum NPC_TYPES
{
    SPRITE,
    ONE_FRAME
};

int FPS;
int FRAMES_RENDERED;

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
int NUM_TARGETS;

int NUM_STATS;
int NUM_AREAS;
int COLLISION_X;
int COLLISION_Y;
int X;
int Y;
int TICK;
int MAP_WIDTH;
int MAP_HEIGHT;
int WAITING_FOR_MESSAGE;
char **STAT_MATRIX;
int IN_BATTLE;
int NUM_STEPS;
int TICKS;
int GAME_SECS;
int ROLL;
int FULLSCREEN_ON;

struct SDL_Color WHITE;
struct SDL_Color GREY;
struct SDL_Color MENU_BACKGROUND;
struct SDL_Color GOLD;
struct SDL_Color RED;
struct SDL_Color BLU;
struct SDL_Color GRN;
struct STRING_LIST **DIALOGUES;
struct INTEGER_LIST **BATTLE_LINEUP;
struct STRING_LIST *NPC_PATHS;
struct STRING_LIST *ENEMY_PATHS;
struct STRING_LIST *BATTLE_BACKGROUNDS;
struct STRING_LIST *BATTLE_CHARACTER_GRAPHICS;
struct STRING_LIST *CHARACTER_NAMES;
struct STRING_LIST *CHARACTER_AGES;
struct STRING_LIST *CHARACTER_JOBS;
struct STRING_LIST *CHARACTER_BIO_PATHS;
struct STRING_LIST *SAVE_PATHS;
struct STRING_LIST **LOAD_SAVE_INFO_STRINGS;
struct STRING_LIST *ENEMIES;
struct SDL_Textures **alpha_textures;

void set_items(int *);
int quit();
int render_thread(void *);
int confirm(int val);
#endif