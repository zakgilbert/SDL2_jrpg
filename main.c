#include "main.h"

int inputs[6];
int NUM_CHARACTERS;
int EDGE_DETECTION[4];
int MOVEMENT_DISABLED;
int *ITEM_QUANTITIES;
int *BAG_QUANTITIES;
int ITEM_QUANTITY;
int ITEMS_IN_BAG;
int IS_MOVING;
char **BAG;
int X;
int Y;
int MAP_WIDTH;
int MAP_HEIGHT;
int TICK;

int main(int argc, char **argv)
{

    set_up_timer();
    int running;
    ITEM_QUANTITY = 4;
    NUM_CHARACTERS = 1;
    ITEMS_IN_BAG = set_item_quanities();
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

    struct Party *party;

    party = malloc(sizeof(struct Party));

    party->character_0 = CREATE_CHARACTER();
    party->character_1 = CREATE_CHARACTER();
    party->character_2 = CREATE_CHARACTER();
    party->character_3 = CREATE_CHARACTER();

    party->character_0->set_stats(party->character_0, "Locke", "32", "Thief", 345, 48, 1000, "graphics/locke_bio.jpg");
    party->character_0->check_stats(party->character_0);

    party->character_1->set_stats(party->character_1, "Terra", "23", "Wizard", 311, 151, 811, "graphics/terra_bio.jpg");
    party->character_1->check_stats(party->character_1);

    party->character_2->set_stats(party->character_2, "Sabin", "21", "Monk", 422, 23, 1522, "graphics/sabin_bio.jpg");
    party->character_2->check_stats(party->character_2);

    party->character_3->set_stats(party->character_3, "Gau", "14", "Bezerker", 353, 3, 933, "graphics/gau_bio.jpg");
    party->character_3->check_stats(party->character_3);

    SDL_Thread *player_input_thread;
    SDL_Thread *update_character_stats_thread;
    SDL_Thread *hand_thread;

    renderer = make_renderer(&window);
    party->character_0->create_character_texture(party->character_0, renderer);
    party->character_1->create_character_texture(party->character_1, renderer);
    party->character_2->create_character_texture(party->character_2, renderer);
    party->character_3->create_character_texture(party->character_3, renderer);

    forest->create_assets(forest, renderer);
    hero->set_texture(hero, renderer, "graphics/LOCKE.png");
    hand->create_texture(hand, "graphics/hand.png", renderer, 233, 11);

    MOVEMENT_DISABLED = 0;
    state = DARK_FOREST;
    player_input_thread = SDL_CreateThread(input_thread, "input_thread", NULL);
    update_character_stats_thread = SDL_CreateThread(update_character_stats, "update_character_stats", party);
    hand_thread = SDL_CreateThread(animate_hand_thread, "animate_hand_thread", hand);

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
            hand->render(hand,renderer);
            SDL_RenderPresent(renderer);
            break;

        case ITEMS_MENU:
            //hand->animate(hand);
            TICK = 1;
            SDL_RenderClear(renderer);
            menu->render_items_menu(menu, renderer, hand);
            hand->render(hand,renderer);
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
    SDL_WaitThread(player_input_thread, NULL);
    SDL_WaitThread(update_character_stats_thread, NULL);
    SDL_WaitThread(hand_thread, NULL);

    forest->destroy(forest);
    hero->destroy(hero);
    menu->destroy(menu);
    hand->destroy(hand);
    free(BAG);
    party->character_0->destroy(party->character_0);
    free(party);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

int update_character_stats(void *ptr)
{
    int is_running;
    struct Party *party = ptr;

    is_running = 1;
    while (is_running)
    {
        if (INPUT == QUIT)
        {
            is_running = 0;
        }
        switch (NUM_CHARACTERS)
        {
        case 1:
            party->character_0->check_stats(party->character_0);
            break;
        case 2:
            party->character_0->check_stats(party->character_0);
            party->character_1->check_stats(party->character_1);
            break;
        case 3:
            party->character_0->check_stats(party->character_0);
            party->character_1->check_stats(party->character_1);
            party->character_2->check_stats(party->character_2);
            break;
        case 4:
            party->character_0->check_stats(party->character_0);
            party->character_1->check_stats(party->character_1);
            party->character_2->check_stats(party->character_2);
            party->character_3->check_stats(party->character_3);
            break;
        default:
            break;
        }

        SDL_Delay(1);
    }
    return 0;
}
int set_item_quanities()
{

    int temp[4] = {3, 2, 1, 0};
    int i, count;

    for (i = 0; i < ITEM_QUANTITY; i++)
    {
        if (temp[i] != 0)
        {
            count++;
        }
        /* code */
    }
    char **inb;
    inb = malloc(sizeof(char *) * count);
    BAG_QUANTITIES = malloc(sizeof(int) * count);

    for (i = 0; i < ITEM_QUANTITY; i++)
    {
        if (temp[i] != 0)
        {
            inb[i] = malloc(sizeof(ITEMS[i]));
            strcat(inb[i], ITEMS[i]);
            BAG_QUANTITIES[i] = temp[i];
        }
    }
    BAG = inb;
    return count;
}
int render_thread(void *ptr)
{
    return 0;
}

void refresh_inputs(int *inputs, int len)
{
    for (int i = 0; i < len; ++i)
    {
        inputs[i] = 0;
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
        printf("\nFrames Rendered Per Second: %d", FRAMES_RENDERED);
        printf("\nTicks Per Second: %ld", TICKS_PER_SECOND);
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
