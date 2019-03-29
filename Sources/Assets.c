
/************************
 *  Assets.c
*/

#include "Assets.h"

void create_load_info()
{
    LOAD_SAVE_INFO_STRINGS = malloc(sizeof(struct STRING_LIST) * 3);
    for (size_t i = 0; i < 3; i++)
    {
        LOAD_SAVE_INFO_STRINGS[i] = CREATE_LIST_STRING(get_state_info(i), 1);
        printf("%s\n", LOAD_SAVE_INFO_STRINGS[i]->list[0]);
    }
}
char **get_state_info(int save_state)
{
    FILE *in;
    int *info = malloc(sizeof(int));
    char *path = malloc(50);
    in = fopen(strcat(strcpy(path, SAVE_PATHS->list[save_state]), "save_state_info.txt"), "r");

    fscanf(in, "%d", &info[0]);

    fclose(in);
    free(path);
    return &CHARACTER_NAMES->list[info[0]];
}
void save(Character **party, Item *bag, int save_state)
{
}
Enemy *load_enemy(int key, struct SDL_Renderer *renderer)
{
    FILE *in;
    char *path = malloc(50);
    Enemy *enemy = CREATE_ENEMY(key, renderer);
    in = fopen(strcat(strcat(strcpy(path, "data/Enemies/"), ENEMIES->list[key]), ".txt"), "r");

    fscanf(in, "%d", &enemy->HP.hp_current);
    enemy->HP.hp_max = enemy->HP.hp_current;

    fscanf(in, "%d", &enemy->MP.mp_current);
    enemy->MP.mp_max = enemy->MP.mp_current;

    fscanf(in, "%d", &enemy->SPD);
    free(path);
    fclose(in);
    return enemy;
}
Item *load_bag(Item *bag, int save_state)
{
    FILE *in;
    int num_items;
    int *items;
    int *item_quantities;
    char *path = malloc(50);

    num_items = 0;
    items = NULL;
    item_quantities = NULL;

    in = fopen(strcat(strcpy(path, SAVE_PATHS->list[save_state]), "bag.txt"), "r");

    fscanf(in, "%d", &num_items);

    items = malloc(sizeof(int) * num_items);
    item_quantities = malloc(sizeof(int) * num_items);

    for (size_t i = 0; i < num_items; i++)
    {
        fscanf(in, "%d", &item_quantities[i]);
    }
    for (size_t k = 0; k < num_items; k++)
    {
        fscanf(in, "%d", &items[k]);
    }
    fclose(in);
    bag->items = items;
    bag->item_quantities = item_quantities;
    bag->items_in_bag = num_items;
    free(path);
    return bag;
}

Character **load_party(int save_state, struct SDL_Renderer *renderer)
{
    FILE *in;
    Character **party;
    int *character_keys;
    int num_members;
    int num_actions;
    char *path = malloc(50);

    num_members = 0;
    num_actions = 0;
    character_keys = NULL;

    in = fopen(strcat(strcpy(path, SAVE_PATHS->list[save_state]), "party.txt"), "r");

    fscanf(in, "%d", &num_members);

    party = malloc(sizeof(Character *) * num_members);
    character_keys = malloc(sizeof(int) * num_members);

    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d", &character_keys[i]);
        party[i] = CREATE_CHARACTER(character_keys[i]);
        party[i]->name = CHARACTER_NAMES->list[character_keys[i]];
        party[i]->age = CHARACTER_AGES->list[character_keys[i]];
        party[i]->job = CHARACTER_JOBS->list[character_keys[i]];
        party[i]->image_path = CHARACTER_BIO_PATHS->list[character_keys[i]];
        party[i]->create_character_texture(party[i], renderer);
    }

    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d %d", &party[i]->HP.current, &party[i]->HP.max);
        sprintf(party[i]->HP.str_max, "%d", party[i]->HP.max);
    }

    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d %d", &party[i]->MP.current, &party[i]->MP.max);
        sprintf(party[i]->MP.str_max, "%d", party[i]->MP.max);
    }

    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d %d", &party[i]->EXP.current, &party[i]->EXP.max);
        sprintf(party[i]->EXP.str_max, "%d", party[i]->EXP.max);
    }

    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d", &party[i]->SPD);
    }
    for (size_t i = 0; i < num_members; i++)
    {
        fscanf(in, "%d", &num_actions);
        party[i]->actions = (int *)malloc(sizeof(int) * num_actions);
        for (size_t k = 0; k < num_actions; k++)
        {
            fscanf(in, "%d", &party[i]->actions[k]);
        }
        party[i]->num_actions = num_actions;
    }
    fclose(in);
    free(path);
    return party;
}
void save_bag(Item *bag, int save_state)
{
    FILE *out;
    char *path = malloc(50);

    out = fopen(strcat(strcpy(path, SAVE_PATHS->list[save_state]), "bag.txt"), "w");

    fprintf(out, "%d\n", bag->items_in_bag);

    for (size_t i = 0; i < bag->items_in_bag - 1; i++)
    {
        fprintf(out, "%d ", bag->item_quantities[i]);
    }
    fprintf(out, "%d\n", bag->item_quantities[bag->items_in_bag - 1]);
    for (size_t i = 0; i < bag->items_in_bag - 1; i++)
    {
        fprintf(out, "%d ", bag->items[i]);
    }
    fprintf(out, "%d\n", bag->items[bag->items_in_bag - 1]);
    fclose(out);
    free(path);
}

void SET_GLOBALS()
{
    TICK = 0;
    ITEM_QUANTITY = 4;
    NUM_CHARACTERS = 4;
    READY_TO_INTERACT = -1;
    WAITING_FOR_MESSAGE = 0;
    INTERACT = OFF;
    NUM_STATS = 4;
    INPUT = NONE;
    NUM_AREAS = 1;
    IN_BATTLE = 0;
    NUM_STEPS = 0;
    TICKS = 0;
    ROLL = -1;

    HERO_WIDTH = 32;
    HERO_HEIGHT = 32;

    WHITE.r = 255;
    WHITE.g = 255;
    WHITE.b = 255;

    GREY.r = 160;
    GREY.g = 160;
    GREY.b = 160;

    MENU_BACKGROUND.r = 52;
    MENU_BACKGROUND.g = 104;
    MENU_BACKGROUND.b = 188;

    GOLD.r = 244;
    GOLD.g = 182;
    GOLD.b = 66;

    RED.r = 255;
    RED.g = 66;
    RED.b = 66;

    GRN.r = 66;
    GRN.g = 255;
    GRN.b = 66;

    BLU.r = 66;
    BLU.g = 66;
    BLU.b = 255;

    MOVEMENT_DISABLED = 0;
    state = DARK_FOREST;
    DIALOGUES = malloc(sizeof(struct STRING_LIST) * 2);
    char *d_temp[8] = {"I am a giant, but im nice",
                       "as long as Im not hungry.",
                       "Where are you traveling",
                       "too? I've seen a lot of",
                       "treasure lately you should",
                       "look around, and see if",
                       "you can find some. I bet",
                       "You'll get lucky..."};

    char *d_yeti[1] = {"I am yeti..."};

    DIALOGUES[0] = CREATE_LIST_STRING(d_temp, 8);
    DIALOGUES[1] = CREATE_LIST_STRING(d_yeti, 1);

    char *p_temp[2] = {"graphics/giga.png", "graphics/yeti.png"};
    NPC_PATHS = CREATE_LIST_STRING(p_temp, 2);

    BATTLE_LINEUP = malloc(sizeof(struct INTEGER_LIST) * NUM_AREAS);
    char *enemy_paths_temp[2] = {"graphics/Kiros.png", "graphics/Samurai.png"};
    ENEMY_PATHS = CREATE_LIST_STRING(enemy_paths_temp, 2);
    int **forest_lineup = malloc(sizeof(int *) * 3);
    int num_forest_lineup[3] = {1, 2, 1};
    for (size_t i = 0; i < 3; i++)
    {
        forest_lineup[i] = malloc(sizeof(int) * num_forest_lineup[i]);
        if (i == 0)
        {
            forest_lineup[i][0] = Kiros;
        }
        else if (i == 1)
        {
            forest_lineup[i][0] = Kiros;
            forest_lineup[i][1] = Samurai;
        }
        else if (i == 2)
        {
            forest_lineup[i][1] = Samurai;
        }
    }

    char *enemy_names[2] = {"Kiros", "Samurai"};
    ENEMIES = CREATE_LIST_STRING(enemy_names, 2);

    BATTLE_LINEUP[0] = CREATE_LIST_INT(forest_lineup, num_forest_lineup, 3);

    BATTLE_BACKGROUNDS = malloc(sizeof(struct STRING_LIST) * NUM_AREAS);
    char *b_bgs_df[1] = {"graphics/dark_forest.png"};
    BATTLE_BACKGROUNDS = CREATE_LIST_STRING(b_bgs_df, 1);

    BATTLE_CHARACTER_GRAPHICS = malloc(sizeof(struct STRING_LIST));
    char *character_battle_graphics[4] = {"graphics/Locke_battle.png", "graphics/Terra_battle.png", "graphics/Sabin_battle.png", "graphics/Gau_battle.png"};
    BATTLE_CHARACTER_GRAPHICS = CREATE_LIST_STRING(character_battle_graphics, 4);

    char *char_names[4] = {"Locke", "Terra", "Sabin", "GAU"};
    CHARACTER_NAMES = CREATE_LIST_STRING(char_names, 4);

    char *char_ages[4] = {"32", "22", "23", "21"};
    CHARACTER_AGES = CREATE_LIST_STRING(char_ages, 4);

    char *char_jobs[4] = {"Thief", "Wizard", "Monk", "Bezerker"};
    CHARACTER_JOBS = CREATE_LIST_STRING(char_jobs, 4);

    char *char_paths[4] = {"graphics/locke_bio.jpg",
                           "graphics/terra_bio.jpg",
                           "graphics/sabin_bio.jpg",
                           "graphics/gau_bio.jpg"};
    CHARACTER_BIO_PATHS = CREATE_LIST_STRING(char_paths, 4);

    char *save_paths[3] = {"data/save/save1/",
                           "data/save/save2/",
                           "data/save/save3/"};

    SAVE_PATHS = CREATE_LIST_STRING(save_paths, 3);
}