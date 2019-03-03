#ifndef JRPG_MESSAGE_H
#define JRPG_MESSAGE_H
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "header.h"
#include "Window.h"

typedef struct _message
{
    void (*destroy)(struct _message *);
    void (*render)(struct _message *, int, int, int, int, int, int);
    void (*line_r)(struct _message *, const char *, int, int, int, int, int, int);
    int (*create_lines)(struct _message *);
    Window *message_background;
    TTF_Font *font;
    int skip;
    struct SDL_Texture *texture;
    struct SDL_Surface *surface;
    struct SDL_Rect rect;

    char * message;

    char * path;

    int seconds_of_existence;
    int frames_of_existence;
    int frame;
    int characters_rendered;
    int lines;
    int line;
    int number_of_characters;
    int characters_per_line;
    int font_size;
    int letter_width;
    int letter_height;
    int num_words;
    

    char ** message_2d;

} Message;

Message *CREATE_MESSAGE(char *, const char *, int, int, int, int, int, int);

#endif