#include "main.h"

int inputs[6];
int NUM_CHARACTERS;
int EDGE_DETECTION[4];
int MOVEMENT_DISABLED;
int ITEM_QUANTITY;
int IS_MOVING;
int REFRESH_ITEMS;
char **BAG;
int X;
int Y;
int MAP_WIDTH;
int MAP_HEIGHT;
int TICK;
char **STAT_MATRIX;

int main(int argc, char **argv)
{

    set_up_timer();
    int running;
    ITEM_QUANTITY = 4;
    NUM_CHARACTERS = 4;
    TICK = 0;
    running = 1;
    refresh_inputs(inputs, 6);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;

    window = make_window("Window");
    Forest *forest = CREATE_FOREST();
    Hero *hero = CREATE_HERO();
    Hand *hand = CREATE_HAND();
    Menu *menu = CREATE_MENU();
    Items *bag = CREATE_BAG();

    const char current_items[3][10] = {
        {"POTION"},
        {"SOFT"},
        {"ETHER"}};

    int quat[3] = {4, 3, 2};

    bag->fill_bag(bag, current_items, quat, 3);

    Character **party = (Character **)malloc(sizeof(Character *) * NUM_CHARACTERS);

    party[0] = CREATE_CHARACTER();
    party[1] = CREATE_CHARACTER();
    party[2] = CREATE_CHARACTER();
    party[3] = CREATE_CHARACTER();

    party[0]->set_stats(party[0], "Locke", "32", "Thief", 345, 48, 1000, "graphics/locke_bio.jpg");
    party[0]->check_stats(party[0]);

    party[1]->set_stats(party[1], "Terra", "23", "Wizard", 311, 151, 811, "graphics/terra_bio.jpg");
    party[1]->check_stats(party[1]);

    party[2]->set_stats(party[2], "Sabin", "21", "Monk", 422, 23, 1522, "graphics/sabin_bio.jpg");
    party[2]->check_stats(party[2]);

    party[3]->set_stats(party[3], "Gau", "14", "Bezerker", 353, 3, 933, "graphics/gau_bio.jpg");
    party[3]->check_stats(party[3]);

    SDL_Thread *player_input_thread;
    SDL_Thread *update_character_stats_thread;
    SDL_Thread *hand_thread;
    SDL_Thread *matrix_thread;

    renderer = make_renderer(&window);
    party[0]->create_character_texture(party[0], renderer);
    party[1]->create_character_texture(party[1], renderer);
    party[2]->create_character_texture(party[2], renderer);
    party[3]->create_character_texture(party[3], renderer);

    forest->create_assets(forest, renderer);
    hero->set_texture(hero, renderer, "graphics/LOCKE.png");
    hand->create_texture(hand, "graphics/hand.png", renderer, 233, 11);

    MOVEMENT_DISABLED = 0;
    state = DARK_FOREST;
    player_input_thread = SDL_CreateThread(input_thread, "input_thread", NULL);
    update_character_stats_thread = SDL_CreateThread(update_character_stats, "update_character_stats", party);
    hand_thread = SDL_CreateThread(animate_hand_thread, "animate_hand_thread", hand);
    matrix_thread = SDL_CreateThread(stat_matrix_thread, "stat_matrix_thread", party);
    party[0]->HP.current = 100;
    while (running)
    {
        start_timer();
        refresh_inputs(EDGE_DETECTION, 4);
        IS_MOVING = 0;
        switch (state)
        {
        case DARK_FOREST:
            movement();
            SDL_RenderClear(renderer);
            forest->render_forest(forest, renderer, hero);
            SDL_RenderPresent(renderer);
            break;

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
        default:
            break;
        }
        // printf("\nHand X: %d\nHand Y: %d", hand->position.x, hand->position.y);
        running = quit();
        FRAMES_RENDERED++;
        delay();
        reset_timer();
    }
    SDL_WaitThread(player_input_thread, NULL);
    SDL_WaitThread(update_character_stats_thread, NULL);
    SDL_WaitThread(hand_thread, NULL);
    SDL_WaitThread(matrix_thread, NULL);

    forest->destroy(forest);
    hero->destroy(hero);
    menu->destroy(menu);
    hand->destroy(hand);
    free(STAT_MATRIX);
    party[0]->destroy_party(party);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

int update_character_stats(void *ptr)
{
    int is_running;
    Character **party = ptr;

    is_running = 1;
    while (is_running)
    {
        if (INPUT == QUIT)
        {
            is_running = 0;
        }
        for (size_t i = 0; i < NUM_CHARACTERS; i++)
        {
            party[i]->check_stats(party[i]);
        }
        SDL_Delay(1);
    }
    return 0;
}

void refresh_inputs(int *array, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        array[i] = 0;
    }
}
int quit()
{
    if (INPUT == QUIT)
    {
        return 0;
    }
    return 1;
}

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
