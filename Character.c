/* Character.c */

#include "Character.h"

static void __destroy(Character *this)
{
    SDL_DestroyTexture(this->character_texture);
    this->character_texture = NULL;

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

void set_party_null(struct Party *party)
{
    party->character_0 = NULL;
    party->character_1 = NULL;
    party->character_2 = NULL;
    party->character_3 = NULL;
}

int count_party(struct Party *party)
{
    int count;
    count = 0;
    if (party->character_0 != NULL)
        count++;
    if (party->character_1 != NULL)
        count++;
    if (party->character_2 != NULL)
        count++;
    if (party->character_3 != NULL)
        count++;

    return count;
}

static void __create_character_texture(Character *this, struct SDL_Renderer *renderer)
{
    struct SDL_Surface * surface = NULL;
    struct SDL_Texture * texture = NULL;
    surface = IMG_Load(this->image_path);

    if (!surface) {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &this->character_rect.w, &this->character_rect.h);
    this->character_texture = texture;
    
}
static void __check_stats(Character *this)
{
    sprintf(this->HP.str_current, "%d", this->HP.current);
    sprintf(this->MP.str_current, "%d", this->MP.current);
    sprintf(this->EXP.str_current, "%d", this->EXP.current);
}
static void __set_stats(Character *this, const char *name, const char *age, char *job, int HP, int MP, int EXP, const char *image_path)
{
    this->name = name;
    this->age = age;
    this->job = job;

    this->HP.current = HP;
    this->HP.max = HP;

    this->MP.current = MP;
    this->MP.max = MP;

    this->EXP.current = EXP;
    this->EXP.max = EXP;

    sprintf(this->EXP.str_max, "%d", this->EXP.max);
    sprintf(this->MP.str_max, "%d", this->MP.max);
    sprintf(this->HP.str_max, "%d", this->HP.max);
    this->image_path = image_path;
}

Character *CREATE_CHARACTER()
{
    Character *this = (Character *)malloc(sizeof(*this));

    this->set_stats = __set_stats;
    this->destroy = __destroy;
    this->check_stats = __check_stats;
    this->create_character_texture = __create_character_texture;
    // this->get_stat_matrix = __get_stat_matrix;

    this->num_stats = 1;

    return this;
}