/* Character.c */

#include "Character.h"

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
static char **__get_stat_matrix(Character *this)
{
    char const * slash = "  /";
    char const * current = this->HP.str_current;
    char const * max = this->HP.str_max;

    unsigned int const size_slash = strlen(slash);
    unsigned int const size_current = strlen(current);
    unsigned int const size_max = strlen(max);

    char * buffer = (char *)malloc(size_current + size_slash + size_max + 1);

    memcpy(buffer ,current, size_current);
    memcpy(buffer + size_current, slash, size_slash);
    memcpy(buffer + size_current + size_slash, max, size_max);
    buffer[size_current + size_slash + size_max] = '\0';
    unsigned int const size_buffer = strlen(buffer);
    char ** stat_matrix = (char **)malloc((sizeof(char *) * this->num_stats) + 1);
    stat_matrix[0] = (char *) malloc(size_buffer + 1);
    memcpy(stat_matrix[0], buffer, size_buffer);
    stat_matrix[0][size_buffer] = '\0';
    stat_matrix[this->num_stats] = '\0';
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
   // this->get_stat_matrix = __get_stat_matrix;

    this->num_stats = 1;

    return this;
}