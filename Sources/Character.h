#ifndef JRPG_CHARACTER_H
#define JRPG_CHARACTER_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

#include "Header.h"

struct Main_Attribute
{
    int current;
    int max;
    char str_current[10];
    char str_max[10];
};


int stat_matrix_thread(void * ptr);
typedef struct __character
{
    void (*destroy)(struct __character *);
    void (*destroy_party)(struct __character **);
    void (*set_stats)(struct __character *, const char *name, const char *age, char *job, int HP, int MP, int EXP, const char *image_path);
    void (*check_stats)(struct __character *);
    void (*create_character_texture) (struct __character *, struct SDL_Renderer *);
    int update_stats;
    struct SDL_Texture * character_texture;
    struct SDL_Rect character_rect;

    const char *image_path;
    const char *name;
    const char *age;
    char *job;
    int num_stats;
    struct Main_Attribute HP;
    struct Main_Attribute MP;
    struct Main_Attribute EXP;
    int key;

} Character;

Character *CREATE_CHARACTER(int key);

struct Party {
    Character * character_0;
    Character * character_1;
    Character * character_2;
    Character * character_3;
};

int count_party(struct Party *);
void set_party_null(struct Party *);
#endif //JRPG_CHARACTER_H
