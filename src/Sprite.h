#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Graphics.h"

struct Sprite_Node
{
    Rect rect;
    const char *key;
};
typedef struct _Sprite
{

    int (*hash_code)(const char *key, const int num, const int attempt);
    int (*hash_code_helper)(const char *key, const int prim, const int size);
    void (*destroy)(struct _Sprite *this);
    void (*insert)(struct _Sprite *this, const char *key, int x, int y, int w, int h);
    Rect* (*search)(struct _Sprite *this, const char *key);
    void (*map)(struct _Sprite *this, const char *keys[], int num_keys);
    struct SDL_Texture *texture;
    Rect pos;
    Rect frame;
    struct Sprite_Node **table;
    const char *name;
    const char *path;
    int rows;
    int cols;
    int num_frames;
    int size, w, h;

} Sprite;
Sprite *CREATE_SPRITE(const char *name, const char *path, int rows, int cols, Renderer renderer, int argc, const char *argv[], int w, int h);

#endif /* SPRITE_H */
