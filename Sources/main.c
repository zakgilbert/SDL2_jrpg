#include "Header.h"
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
#include "Collision.h"

void SET_GLOBALS()
{
    TICK = 0;
    ITEM_QUANTITY = 4;
    NUM_CHARACTERS = 4;
    READY_TO_INTERACT = 0;
    WAITING_FOR_MESSAGE = 0;
    INTERACT = OFF;
    NUM_STATS = 4;
    INPUT = NONE;
    NUM_AREAS = 1;

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
}

int main(int argc, char **argv)
{
    set_up_timer(60);
    int running;
    char *current_message;
    SET_GLOBALS();
    running = 1;
    current_message = malloc(30);

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
    Area *dark_forest = CREATE_FOREST(DARK_FOREST);
    Hero *hero = CREATE_HERO();
    Hand *hand = CREATE_HAND();
    Menu *menu = CREATE_MENU();
    Items *bag = CREATE_BAG();
    Collision *game_collision = CREATE_COLLISION();

    Message *message_being_displayed;
    Message *my_test_mesage = CREATE_MESSAGE("ponde___.ttf", "The theif locke awakes in a strange daze, surrounded by a dark_forest that he does not recognize. ", 10, 50, 100, 300, 100, 12);
    my_test_mesage->create_lines(my_test_mesage);

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
    party[0]->create_character_texture(party[0], renderer);
    party[1]->create_character_texture(party[1], renderer);
    party[2]->create_character_texture(party[2], renderer);
    party[3]->create_character_texture(party[3], renderer);

    int dark_forest_items[10] = {ETHER, SOFT, PHOENIX_DOWN, POTION, SOFT, ETHER, SOFT, PHOENIX_DOWN, POTION, POTION};

    int dark_forest_items_x[10] = {100, 200, 300, 100, 200, 300, 100, 200, 300, 100};

    int dark_forest_items_y[10] = {100, 200, 300, 100, 200, 300, 100, 200, 300, 100};

    dark_forest->create_assets(dark_forest, renderer, game_collision, dark_forest_items, 10, dark_forest_items_x, dark_forest_items_y);

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
        IS_MOVING = 0;
        refresh_inputs(EDGE_DETECTION, 4, movement());

        switch (state)
        {
        case DARK_FOREST:
            if (state == MESSAGE && WAITING_FOR_MESSAGE != -1)
            {
                SDL_RenderClear(renderer);
                dark_forest->render_area(dark_forest, renderer, hero, bag, current_message);
                break;
            }
            else
            {
                SDL_RenderClear(renderer);
                strcpy(current_message, dark_forest->render_area(dark_forest, renderer, hero, bag, current_message));
                SDL_RenderPresent(renderer);
                // printf("\n\"%s\" is stored at %p.", current_message, current_message);
                break;
            }
        case MAIN_MENU:
            // hand->animate(hand);
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_main_menu(menu, renderer, hand, party);
            hand->render(hand, renderer);
            SDL_RenderPresent(renderer);
            break;

        case ITEMS_MENU:
            //hand->animate(hand);
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
            message_being_displayed = ONE_LINER("ponde___.ttf", current_message, 0, 0, 20, 10);
            message_being_displayed->render_one_liner(message_being_displayed, renderer);
            SDL_RenderPresent(renderer);
            wait_for_okay();
            state = previous_state;
            previous_state = MESSAGE;
            WAITING_FOR_MESSAGE = -1;
            break;
        default:
            break;
        }
        // printf("\nHand X: %d\nHand Y: %d", hand->position.x, hand->position.y);
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
    free(current_message);
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