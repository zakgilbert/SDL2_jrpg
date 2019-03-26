
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
#include "Assets.h"

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
    renderer = make_renderer(&window);

    Area *dark_forest = CREATE_AREA(DARK_FOREST);
    Hero *hero = CREATE_HERO();
    Hand *hand = CREATE_HAND();
    Menu *menu = CREATE_MENU();
    Item *bag = CREATE_BAG();
    Collision *game_collision = CREATE_COLLISION();

    bag = load_bag(bag, 0);

    SDL_Thread *player_input_thread;
    SDL_Thread *hand_thread;
    SDL_Thread *matrix_thread;

    Battle *current_battle = NULL;

    Character **party = load_party(0, renderer);

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

        case SAVE:
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_save_menu(menu, renderer, hand);
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
                current_battle = CREATE_BATTLE(previous_state, 0, renderer, party, 1);
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
    save_bag(bag, 0);
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