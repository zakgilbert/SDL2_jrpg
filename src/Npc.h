#ifndef JRPG_NPC_H
#define JRPG_NPC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
#include "Graphics.h"

typedef struct _Npc
{
    void (*destroy)(struct _Npc *);
    void (*render)(struct _Npc *, struct SDL_Renderer *renderer);
    int (*interact)(struct _Npc *);
    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    struct SDL_Rect rect2;

    int key;
    int index;
    int x, y;
    int ready_to_interact;
    enum NPC_TYPES type;
} Npc;

Npc *CREATE_NPC(struct SDL_Renderer *renderer, int x, int y, int index, int key, char *path, int type);
void render_npc(void *obj, struct SDL_Renderer *renderer);

#endif