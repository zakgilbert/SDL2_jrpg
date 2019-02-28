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

static void __destroy_party(Character **party)
{
    int i;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        party[i]->destroy(party[i]);
    }
    free(party);
    party = NULL;
}

int stat_matrix_thread(void *ptr)
{
    int is_running;
    is_running = 1;
    Character **p = ptr;
    char *slash = " /";
    char *HP = "HP:   ";
    char *MP = "MP:   ";
    char *EXP = "EXP:  ";
    size_t slash_size = (strlen(slash) + 1);
    size_t size_HP_string = (strlen(HP) + 1);
    size_t size_MP_string = (strlen(MP) + 1);
    size_t size_EXP_string = (strlen(EXP) + 1);

    STAT_MATRIX = (char **)malloc(sizeof(char *) * (NUM_CHARACTERS * 4));
    while (is_running)
    {
        int j = 0;
        for (size_t i = 0; i < NUM_CHARACTERS; i++)
        {
            p[i]->check_stats(p[i]);
            size_t name_size = (strlen(p[i]->name) + 1);
            size_t HP_current_size = (strlen(p[i]->HP.str_current) + 1);
            size_t MP_current_size = (strlen(p[i]->MP.str_current) + 1);
            size_t EXP_current_size = (strlen(p[i]->EXP.str_current) + 1);

            size_t HP_max_size = (strlen(p[i]->HP.str_max) + 1);
            size_t MP_max_size = (strlen(p[i]->MP.str_max) + 1);
            size_t EXP_max_size = (strlen(p[i]->EXP.str_max) + 1);

            char *buffer = malloc(name_size);
            strcpy(buffer, p[i]->name);
            size_t buffer_size = (strlen(buffer) + 1);

            STAT_MATRIX[j] = (char *)malloc(sizeof(buffer_size));
            strcat(STAT_MATRIX[j], buffer);

            j++;

            buffer = realloc(buffer, size_HP_string + HP_current_size + slash_size + HP_max_size);
            strcpy(buffer, HP);
            strcat(buffer, p[i]->HP.str_current);
            strcat(buffer, slash);
            strcat(buffer, p[i]->HP.str_max);

            buffer_size = (strlen(buffer) + 1);

            STAT_MATRIX[j] = (char *)malloc(sizeof(buffer_size));
            strcat(STAT_MATRIX[j], buffer);

            j++;

            buffer = realloc(buffer, size_MP_string + MP_current_size + slash_size + MP_max_size);
            strcpy(buffer, MP);
            strcat(buffer, p[i]->MP.str_current);
            strcat(buffer, slash);
            strcat(buffer, p[i]->MP.str_max);

            buffer_size = (strlen(buffer) + 1);

            STAT_MATRIX[j] = (char *)malloc(sizeof(buffer_size));
            strcat(STAT_MATRIX[j], buffer);

            j++;

            buffer = realloc(buffer, size_EXP_string + EXP_current_size + slash_size + EXP_max_size);
            strcpy(buffer, EXP);
            strcat(buffer, p[i]->EXP.str_current);
            strcat(buffer, slash);
            strcat(buffer, p[i]->EXP.str_max);

            buffer_size = (strlen(buffer) + 1);

            STAT_MATRIX[j] = (char *)malloc(sizeof(buffer_size));
            strcat(STAT_MATRIX[j], buffer);
            j++;
        }
        if (INPUT == QUIT)
        {
            is_running = 0;
        }
        SDL_Delay(1);
    }
    return 0;
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
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
    surface = IMG_Load(this->image_path);

    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
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
    this->destroy_party = __destroy_party;
    // this->get_stat_matrix = __get_stat_matrix;

    this->num_stats = 1;

    return this;
}