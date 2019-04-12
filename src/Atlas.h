#ifndef ATLAS_H
#define ATLAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_platform.h>
#include "Header.h"
#include "Graphics.h"
#include "Assets.h"
#define PRIME_1 (163)
#define PRIME_2 (151)

int hash_code(const char *letter, const int num, const int attempt);
int hash(const char *letter, const int prime, const int size);

struct Alpha_Node
{
    struct SDL_Texture *texture;
    struct SDL_Rect rect;
    char *key;
};
struct Alpha_Node *new_alpha_node(const char *key, const char *path, struct SDL_Renderer *renderer);
typedef struct _Atlas
{
    void (*destroy)(struct _Atlas *this);
    void (*insert)(struct _Atlas *this, const char *key, struct SDL_Renderer *renderer, const char *path);
    struct Alpha_Node* (*search)(struct _Atlas *this, const char *key);
    void (*map)(struct _Atlas *this, struct SDL_Renderer *renderer);
    void (*render)(struct Alpha_Node *node, struct SDL_Renderer *renderer);
    struct Alpha_Node **letters;
    int size;
    int count;

} Atlas;
Atlas *CREATE_ATLAS();
void render_letter(void *obj, struct SDL_Renderer *renderer);
#endif /* ATLAS_H */
