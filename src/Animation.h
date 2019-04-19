#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

#include "Header.h"
#include "Graphics.h"
#include "Render.h"
#include "Sprite.h"

struct Sprite_Packet
{
    struct SDL_Texture *texture;
    struct SDL_Rect rect_1;
    struct SDL_Rect rect_2;
    int w, h;
};
typedef struct _Animation
{
    void (*destroy)(struct _Animation *this);
    render_function(*render);
    Sprite *charge_spell;
    Sprite *fire_1;

} Animation;
Animation *CREATE_ANIMATION(struct SDL_Renderer *renderer);

#endif /* ANIMATION_H */
