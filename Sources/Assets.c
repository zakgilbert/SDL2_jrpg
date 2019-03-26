
/************************
 *  Assets.c
*/

#include "Assets.h"

Item *load_bag(Item *bag, int save_state)
{
    FILE *in;
    int num_items;
    int *items;
    int *item_quantities;

    num_items = 0;
    items = NULL;
    item_quantities = NULL;

    in = fopen("data/bag.txt", "r");

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
    return bag;
}

Character **load_party(int save_state, struct SDL_Renderer *renderer)
{
    FILE *in;
    Character **party;
    int *character_keys;
    int num_members;

    num_members = 0;
    character_keys = NULL;

    in = fopen("data/party.txt", "r");

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
    fclose(in);
    return party;
}
void save_bag(Item *bag, int save_state)
{
    FILE *out;

    out = fopen("data/bag.txt", "w");

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
    char *enemy_paths_temp[1] = {"graphics/knight_bez.png"};
    ENEMY_PATHS = CREATE_LIST_STRING(enemy_paths_temp, 1);
    int forest_lineup[1][1] = {KNIGHT_BEZ_MOUNT};
    int num_forest_lineup[1] = {1};

    BATTLE_LINEUP[0] = CREATE_LIST_INT(forest_lineup, num_forest_lineup, 1);

    BATTLE_BACKGROUNDS = malloc(sizeof(struct STRING_LIST) * NUM_AREAS);
    char *b_bgs_df[1] = {"graphics/dark_forest.png"};
    BATTLE_BACKGROUNDS = CREATE_LIST_STRING(b_bgs_df, 1);

    BATTLE_CHARACTER_GRAPHICS = malloc(sizeof(struct STRING_LIST));
    char *character_battle_graphics[1] = {"graphics/Locke_battle.png"};
    BATTLE_CHARACTER_GRAPHICS = CREATE_LIST_STRING(character_battle_graphics, 1);

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
}