#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"
#include "Assets.h"
#include "Atlas.h"
#include "Window.h"
#include "Line.h"
#include "Render.h"

typedef struct _Dialogue
{
    void (*destroy)(struct _Dialogue *this);
    void (*create_lines)(struct _Dialogue *this, Atlas *atlas);
    int (*add_lines)(struct _Dialogue *this, Render_Q *q);

    Window *window;
    Atlas *atlas;

    const char **lines;
    int x, y;
    int num_lines;
    int index;

} Dialogue;
Dialogue *CREATE_DIALOGUE(Atlas *atlas, const char **lines, int x, int y, int num_lines);

#endif /* DIALOGUE_H */
