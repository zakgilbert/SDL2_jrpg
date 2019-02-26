/* Character.c */

#include "Character.h"

int update_character_stats(void *characters)
{
    int i, is_running;
    Character **temp_characters = characters;

    is_running = 1;
    while (is_running)
    {
        if (INPUT == QUIT)
        {
            is_running = 0;
        }
        for (i = 0; i < NUM_CHARACTERS; i++)
        {
            temp_characters[i]->check_stats(temp_characters[i]);
        }
    }
    return 0;
}

static char **__get_stat_matrix(Character *this)
{
    char back_slash[2] = " /";
    char *buffer;
    char **stat_matrix;
    int bytes = 20;

    buffer = malloc(bytes);
    stat_matrix = malloc(sizeof(char *) * this->num_stats);

    strcat(buffer, this->HP.str_current);
    strcat(buffer, back_slash);
    strcat(buffer, this->HP.str_max);
    stat_matrix[0] = malloc(strlen(buffer));
    strcat(stat_matrix[0], buffer);
    free(buffer);
    buffer = malloc(bytes);
    strcat(buffer, this->MP.str_current);
    strcat(buffer, back_slash);
    strcat(buffer, this->MP.str_max);
    stat_matrix[1] = malloc(strlen(buffer));
    strcat(stat_matrix[1], buffer);
    free(buffer);
    buffer = malloc(bytes);
    strcat(buffer, this->EXP.str_current);
    strcat(buffer, back_slash);
    strcat(buffer, this->EXP.str_max);
    stat_matrix[2] = malloc(strlen(buffer));
    strcat(stat_matrix[2], buffer);
    free(buffer);

    return stat_matrix;
}

static void __destroy(Character *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
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
}

Character *CREATE_CHARACTER()
{
    Character *this = (Character *)malloc(sizeof(*this));
    this->set_stats = __set_stats;
    this->destroy = __destroy;
    this->check_stats = __check_stats;
    this->get_stat_matrix = __get_stat_matrix;

    this->num_stats = 3;
}