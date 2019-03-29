
#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Graphics.h"

struct Enemy_Stat
{
    char *name;
    int hp_current;
    int hp_max;
    int mp_current;
    int mp_max;
};

typedef struct _Enemy
{
    void (*destroy)(struct _Enemy *this);
    void (*render)(struct _Enemy *this, struct SDL_Renderer *renderer);

    struct Enemy_Stat HP;
    struct Enemy_Stat MP;
    int update_stats;
    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    int SPD;
    int key;
    int type;
} Enemy;
Enemy *CREATE_ENEMY(int key, struct SDL_Renderer * renderer);
#endif /* ENEMY_H */
