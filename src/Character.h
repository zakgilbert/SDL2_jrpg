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
#include "Hero.h"
#include "Render.h"
#include "Window.h"
#include "Atlas.h"
#include "Line.h"
#include "Words.h"
#include "Animation.h"
#include "Sprite.h"

struct Main_Attribute
{
    int current;
    int max;
    char str_current[10];
    char str_max[10];
    char display[50];
    char name[10];
};
void stand_battle_ani(struct SDL_Rect *rect);
int cast_1_battle_ani(struct SDL_Rect *rect);
int cast_2_battle_ani(struct SDL_Rect *rect);
int handler_party_stats(void *party);
typedef struct _Character
{
    /**
     * destroy
     */
    void (*destroy)(struct _Character *);
    void (*destroy_party)(struct _Character **);
    void (*check_stats)(struct _Character *);
    void (*create_battle_texture)(struct _Character *, struct SDL_Renderer *renderer, int i);
    render_function(*render_battle_textures);
    void (*render_bio_image)(struct _Character *this, struct SDL_Renderer *renderer);
    int (*update_party_stats)(struct _Character **);
    int (*cast)(struct _Character *, Render_Q *q);
    int (*cast_ptr[2])(struct SDL_Rect *rect);
    Uint32 (*speed_round)(struct _Character *this);
    int (*set_battle_actions)(struct _Character *this, Atlas *at, Render_Q *q);
    GET_DATA(*get_data);
    change_animation_pos(*curent_spell);
    int (*get_current_state_options)(struct _Character *this);
    struct SDL_Texture *texture;
    struct SDL_Rect rect;

    Sprite *battle_spr;
    struct SDL_Texture *b_texture;
    struct SDL_Rect b_rect_1;
    struct SDL_Rect b_rect_2;

    struct Main_Attribute HP;
    struct Main_Attribute MP;
    struct Main_Attribute EXP;
    Animation *animation;

    int *spells;
    int num_spells;
    const char *image_path;
    const char *name;
    const char *age;
    char *job;
    Uint32 SPD;
    int key;
    int type;
    int *actions;
    int num_actions;
    int num_stats;
    int in_action_queue;
    int update_stats;
    int animation_total_frames;
    int current_animation_frame;
    int ani_i;
    int in_animation;
    int ready;
    enum battle_states current_state;
    CHARACTER_BATTLE_FRAME_ENUM current_sprite_frame;
    int index;

} Character;

Character *CREATE_CHARACTER(int key, struct SDL_Renderer *renderer);

struct Party
{
    Character *character_0;
    Character *character_1;
    Character *character_2;
    Character *character_3;
};

int count_party(struct Party *);
void set_party_null(struct Party *);
void render_character_bio_image(void *obj, struct SDL_Renderer *renderer);
#endif
