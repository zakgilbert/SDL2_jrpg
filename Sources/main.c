
#include "Header.h"
#include "H.h"
#include "Words.h"
#include "Graphics.h"
#include "Window_and_Renderer.h"
#include "Floor.h"
#include "Hero.h"
#include "Item.h"
#include "Area.h"
#include "Player_Input.h"
#include "Movement.h"
#include "Window.h"
#include "Menu.h"
#include "Hand.h"
#include "Character.h"
#include "Affect.h"
#include "Message.h"
#include "Time.h"
#include "Lootable.h"
#include "Npc.h"
#include "Collision.h"
#include "Battle.h"

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
}

int main(int argc, char **argv)
{
    set_up_timer(60);
    int running;
    SET_GLOBALS();
    running = 1;

    refresh_inputs(USER_INPUTS, 6, 1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;

    window = make_window("Window");
    Area *dark_forest = CREATE_AREA(DARK_FOREST);
    Hero *hero = CREATE_HERO();
    Hand *hand = CREATE_HAND();
    Menu *menu = CREATE_MENU();
    Items *bag = CREATE_BAG();
    Collision *game_collision = CREATE_COLLISION();

    int party_items[3] = {POTION, ETHER, SOFT};
    int quat[3] = {4, 3, 2};

    bag->fill_bag(bag, party_items, quat, 3);

    Character **party = (Character **)malloc(sizeof(Character *) * NUM_CHARACTERS);

    party[0] = CREATE_CHARACTER();
    party[1] = CREATE_CHARACTER();
    party[2] = CREATE_CHARACTER();
    party[3] = CREATE_CHARACTER();

    party[0]->set_stats(party[0], "Locke", "32", "Thief", 1000, 48, 1000, "graphics/locke_bio.jpg");
    party[0]->check_stats(party[0]);

    party[1]->set_stats(party[1], "Terra", "23", "Wizard", 311, 151, 811, "graphics/terra_bio.jpg");
    party[1]->check_stats(party[1]);

    party[2]->set_stats(party[2], "Sabin", "21", "Monk", 422, 23, 1522, "graphics/sabin_bio.jpg");
    party[2]->check_stats(party[2]);

    party[3]->set_stats(party[3], "Gau", "14", "Bezerker", 353, 3, 933, "graphics/gau_bio.jpg");
    party[3]->check_stats(party[3]);

    SDL_Thread *player_input_thread;
    SDL_Thread *hand_thread;
    SDL_Thread *matrix_thread;

    renderer = make_renderer(&window);
    Battle *current_battle = NULL;
    party[0]->create_character_texture(party[0], renderer);
    party[1]->create_character_texture(party[1], renderer);
    party[2]->create_character_texture(party[2], renderer);
    party[3]->create_character_texture(party[3], renderer);

    int dark_forest_npcs[2] = {GIGAS, SASH};
    int dark_forest_npc_types[2] = {ONE_FRAME, SPRITE};
    int dark_forest_npcs_x[2] = {400, 350};
    int dark_forest_npcs_y[2] = {400, 350};

    int dark_forest_items[2] = {POTION, ETHER};
    int dark_forest_items_x[2] = {300, 400};
    int dark_forest_items_y[2] = {300, 300};

    dark_forest->create_assets(dark_forest, renderer, game_collision, dark_forest_items, 2,
                               dark_forest_npcs, dark_forest_npc_types, 2,
                               dark_forest_items_x, dark_forest_items_y, dark_forest_npcs_x, dark_forest_npcs_y);

    hero->set_texture(hero, renderer, "graphics/LOCKE.png");
    hand->create_texture(hand, "graphics/hand.png", renderer, 233, 11);

    player_input_thread = SDL_CreateThread(input_thread, "input_thread", NULL);
    hand_thread = SDL_CreateThread(animate_hand_thread, "animate_hand_thread", hand);
    matrix_thread = SDL_CreateThread(stat_matrix_thread, "stat_matrix_thread", party);
    party[0]->HP.current = 100;
    party[1]->MP.current = 0;

    while (running)
    {
        start_timer();
        refresh_inputs(EDGE_DETECTION, 4, movement());
        game_collision->update_collidables(game_collision, state);

        switch (state)
        {
        case DARK_FOREST:
            SDL_RenderClear(renderer);
            Message *message_being_displayed = dark_forest->render_area(dark_forest, renderer, hero, bag);
            SDL_RenderPresent(renderer);
            break;

        case MAIN_MENU:
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_main_menu(menu, renderer, hand, party);
            hand->render(hand, renderer);
            SDL_RenderPresent(renderer);
            break;

        case ITEMS_MENU:
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_items_menu(menu, renderer, hand, bag);
            hand->render(hand, renderer);
            SDL_RenderPresent(renderer);
            break;
        case USE_ITEM:
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_use_item_menu(menu, renderer, hand, party, bag);
            hand->render(hand, renderer);
            SDL_RenderPresent(renderer);
            break;
        case CONFIG:
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_config_menu(menu, renderer, hand);
            hand->render(hand, renderer);
            SDL_RenderPresent(renderer);
            break;

        case MESSAGE:
            if (message_being_displayed->type == ONE_LINER)
            {
                message_being_displayed->render_one_liner(message_being_displayed, renderer);
                SDL_RenderPresent(renderer);
                wait_for_okay();
                state = previous_state;
                previous_state = MESSAGE;
                message_being_displayed->destroy(message_being_displayed);
                message_being_displayed = NULL;
            }
            else if (message_being_displayed->type == DIALOGUE)
            {
                while (!message_being_displayed->render_dialogue(message_being_displayed, renderer))
                {
                    SDL_RenderPresent(renderer);
                    wait_for_okay();
                    USER_INPUTS[4] = 0;
                }
                state = previous_state;
                previous_state = MESSAGE;
                message_being_displayed->destroy(message_being_displayed);
                message_being_displayed = NULL;
                printf("\nwe are finished here\n\n");
            }
            break;
        case BATTLE:
            if (current_battle == NULL)
            {
                current_battle = CREATE_BATTLE(previous_state, 0, renderer);
            }

            SDL_RenderClear(renderer);
            current_battle->render(current_battle, renderer);
            SDL_RenderPresent(renderer);
            break;
        default:
            break;
        }
        running = quit();
        FRAMES_RENDERED++;
        delay();
        reset_timer();
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &menu->transition);
    SDL_RenderPresent(renderer);
    SDL_WaitThread(player_input_thread, NULL);
    SDL_WaitThread(hand_thread, NULL);
    SDL_WaitThread(matrix_thread, NULL);

    dark_forest->destroy(dark_forest);
    hero->destroy(hero);
    menu->destroy(menu);
    hand->destroy(hand);
    bag->destroy(bag);

    free(STAT_MATRIX);
    party[0]->destroy_party(party);
    SDL_DestroyRenderer(renderer);
    SDL_Delay(400);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

int refresh_inputs(int *array, int size, int bol)
{
    if (!bol)
    {
        return 0;
    }
    int i;

    for (i = 0; i < size; i++)
    {
        array[i] = 0;
    }
    return 1;
}
int quit()
{
    if (INPUT == QUIT)
    {
        return 0;
    }
    return 1;
}
/*
void set_up_timer()
{
    FPS = 60;
    DELTA = 0;
    TIME_PER_TICK = 1000000000 / (FPS / 2);
    TIME_LAST = SDL_GetPerformanceCounter();
    NANO_TIMER = 0;
    FRAMES_RENDERED = 0;
    TICKS_PER_SECOND = 0;
    TIME_DELAY_PER_SECOND = 0;
}

void start_timer()
{
    TIME_NOW = SDL_GetPerformanceCounter();
    DELTA += (double)((TIME_NOW - TIME_LAST) / TIME_PER_TICK);
    NANO_TIMER = TIME_NOW - TIME_LAST;
    TICKS_PER_SECOND += NANO_TIMER;
    TIME_LAST = TIME_NOW;
}

int check_delta()
{
    if (DELTA >= 1)
    {
        return 1;
    }
    return 0;
}

void update_delta()
{
    DELTA--;
    FRAMES_RENDERED++;
}

void reset_timer()
{

    if (TICKS_PER_SECOND >= SDL_GetPerformanceFrequency())
    {
        // printf("\nFrames Rendered Per Second: %d", FRAMES_RENDERED);
        // printf("\nTicks Per Second: %ld", TICKS_PER_SECOND);
        FRAMES_RENDERED = 0;
        TICKS_PER_SECOND = 0;
    }
}

void delay()
{
    if (NANO_TIMER < TIME_PER_TICK)
    {
        TIME_DELAY_PER_SECOND = ((TIME_PER_TICK - NANO_TIMER) / (SDL_GetPerformanceFrequency() * 0.001));
        SDL_Delay(TIME_DELAY_PER_SECOND);
        // printf("\nTimeDelayed is: %Lf", TIME_DELAY_PER_SECOND);
        //   printf("\nTimeDelayed int is: %Lf", TIME_DELAY_PER_SECOND);
    }
}
*/