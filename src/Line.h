#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Atlas.h"
#include "Window.h"

struct Letter
{
    const char *letter;
    struct SDL_Rect rect;
    struct SDL_Texture *texture;
};
typedef struct _Line
{
    void (*destroy)(struct _Line *this);
    void (*set_letters)(struct _Line *this);

    struct SDL_Texture *(*get_texture)(struct _Line *this, int i);
    void (*render_letter)(struct SDL_Renderer *renderer, struct SDL_Texture *texture, struct SDL_Rect *rect);
    void (*change_cords)(struct _Line *this, int x, int y);

    struct Letter **letters;
    Atlas *atlas;
    int num_let;
    const char *line;
    int x, y;
    int num_lines;
    int update_x, update_y;
    Window *window;

} Line;

Line *CREATE_LINE(Atlas *atlas, const char *line, int x, int y);

Line *CREATE_LINE_WINDOW(Atlas *atlas, const char *line, int x, int y);

struct Letter *NEW_LETTER(const char *letter, int x, int y);
void render_line(void *obj, struct SDL_Renderer *renderer);
void destroy_line(void *obj);
#endif /* LINE_H */
