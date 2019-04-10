#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Header.h"
typedef struct _Text
{
    void (*destroy)(struct _Text *this);
    void (*render)(struct _Text *this, struct SDL_Renderer *renderer);
    struct SDL_Rect rect;
    struct SDL_Surface *surface;
    struct SDL_Texture *texture;
    SDL_Color color;
    const char *text;
    TTF_Font *font;
} Text;
Text *CREATE_TEXT(int x, int y, SDL_Color color, TTF_Font *font, const char *text);
void text_destroy(void *obj);
void render_text(void *obj, struct SDL_Renderer *renderer);
int skip(TTF_Font *font, const char *path, int size);
void open_font(void *obj, struct SDL_Renderer *renderer);
void close_font(void *obj, struct SDL_Renderer *renderer);
#endif /* TEXT_H */
