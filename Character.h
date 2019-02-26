#ifndef JRPG_CHARACTER_H
#define JRPG_CHARACTER_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "header.h"

struct Main_Attribute
{
    int current;
    int max;
    char str_current[10];
    char str_max[10];
};

int update_character_stats(void *characters);

typedef struct __character
{
    void (*destroy)(struct __character *);
    void (*set_stats)(struct __character *, const char *name, const char *age, char *job, int HP, int MP, int EXP, const char *image_path);
    void (*check_stats)(struct __character *);
    void (*check_stats_wrapper)(struct __character *);
    char ** (*get_stat_matrix)(struct __character *);

    const char *name;
    const char *age;
    char *job;
    int num_stats;
    struct Main_Attribute HP;
    struct Main_Attribute MP;
    struct Main_Attribute EXP;

} Character;

Character *CREATE_CHARACTER();
#endif //JRPG_CHARACTER_H
