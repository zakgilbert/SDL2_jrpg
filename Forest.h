//
// Created by zachary on 1/23/19.
//

#ifndef JRPG_FOREST_H
#define JRPG_FOREST_H

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Floor.h"
#include "Hero.h"
#include "header.h"


typedef struct __forest {
    Floor * floor;
    Floor * trees;

    void (*destroy) (struct __forest *);
    void (*create_assets) (struct __forest *, struct SDL_Renderer *);
    void (*render_forest) (struct __forest *, struct SDL_Renderer *, Hero *);


}Forest;

Forest * CREATE_FOREST();
#endif //JRPG_FOREST_H
