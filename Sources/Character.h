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
#include "Graphics.h"

struct Main_Attribute
{
    int current;
    int max;
    char str_current[10];
    char str_max[10];
    char display[50];
    char name[10];
};

typedef struct __character
{
    void (*destroy)(struct __character *);
    void (*destroy_party)(struct __character **);
    void (*set_stats)(struct __character *, const char *name, const char *age, char *job, int HP, int MP, int EXP, const char *image_path);
    void (*check_stats)(struct __character *);
    void (*create_character_texture)(struct __character *, struct SDL_Renderer *);
    void (*create_battle_textures)(struct __character *, struct SDL_Renderer *renderer);
    void (*render_battle_textures)(struct __character *, struct SDL_Renderer *renderer);
    int (*update_party_stats)(struct __character **);
    int update_stats;
    struct SDL_Texture *character_texture;
    struct SDL_Rect character_rect;
    struct SDL_Texture **textures_party;
    struct SDL_Rect party_rect_1;
    struct SDL_Rect party_rect_2;

    const char *image_path;
    const char *name;
    const char *age;
    char *job;
    int *actions;
    int num_actions;
    int num_stats;
    int in_action_queue;
    struct Main_Attribute HP;
    struct Main_Attribute MP;
    struct Main_Attribute EXP;
    int SPD;
    int key;
    int type;

} Character;

Character *CREATE_CHARACTER(int key);

struct Party
{
    Character *character_0;
    Character *character_1;
    Character *character_2;
    Character *character_3;
};

int count_party(struct Party *);
void set_party_null(struct Party *);
#endif //JRPG_CHARACTER_H
