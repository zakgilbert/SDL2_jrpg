
#include "Header.h"
#include "H.h"
#include "Render.h"
#include "Words.h"
#include "Graphics.h"
#include "Floor.h"
#include "Hero.h"
#include "Item.h"
#include "Area.h"
#include "Player_Input.h"
#include "Movement.h"
#include "Window.h"
#include "Menu.h"
#include "Hand.h"
#include "Atlas.h"
#include "Character.h"
#include "Affect.h"
#include "Message.h"
#include "Time.h"
#include "Lootable.h"
#include "Npc.h"
#include "Collision.h"
#include "Ba.h"
#include "Assets.h"
#include "Enemy.h"
#include "Battle_Q.h"
#include "Text.h"
#include "Line.h"

int main(int argc, char **argv)
{
    int i;
    key_state = (Uint8 *)SDL_GetKeyboardState(NULL);
    set_up_timer(60);
    SET_GLOBALS();
    create_load_info();
    refresh_inputs(USER_INPUTS, 6, 1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    Atlas *letters = CREATE_ATLAS();
    Hero *hero = CREATE_HERO();
    Hand *hand = CREATE_HAND();
    Item *bag = CREATE_BAG();
    Area *dark_forest = CREATE_AREA(DARK_FOREST, hero, bag);
    Collision *game_collision = CREATE_COLLISION(hero);
    r_Q = CREATE_RENDER_Q();
    letters->map(letters, renderer);

    bag = load_bag(bag, 0);

    SDL_Thread *hand_thread;
    SDL_Thread *input_thread;

    /**
        Battle *current_battle = NULL;
*/
    Ba *current_ba = NULL;

    Character **party = load_party(0, renderer);

    Menu *menu = CREATE_MENU(party, hand, bag, letters);
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

    hero->set_texture(hero, renderer, "graphics/locke_map.png");
    hand->create_texture(hand, "graphics/hand.png", renderer, 233, 11);

    hand_thread = SDL_CreateThread(animate_hand_thread, "animate_hand_thread", hand);
    input_thread = SDL_CreateThread(input_handler, "input_handler", NULL);
    SDL_DetachThread(input_thread);
    party[0]->in_animation = -1;
    FILE *data = fopen("data.txt", "w");
    while (!EXIT())
    {
        for (i = 0; i < 1; i++)
        {
            fprintf(data, "%s", party[i]->get_data(party[i]));
        }

        start_timer();
        movement();
        game_collision->update_collidables(game_collision, state);
        set_fullscreen(window, hero);
        r_Q = r_Q->render(r_Q, renderer);

        switch (state)
        {
        case DARK_FOREST:
            dark_forest->render_area(dark_forest);
            break;

        case MAIN_MENU:
            TICK = 1;
            menu->update_main(menu);
            /**
            menu->update_main_menu(menu);
*/
            break;

        case ITEMS_MENU:
            TICK = 1;
            menu->update_items_menu(menu);
            /**
                menu->update_items_menu(menu);
*/
            break;

        case USE_ITEM:
            TICK = 1;
            menu->update_use_item(menu);
            /**
                menu->update_use_items_menu(menu);
*/
            break;

        case CONFIG:
            TICK = 1;
            menu->update_config(menu);
            /**
                menu->update_config(menu);
*/
            break;

            /**
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
                USER_INPUTS[4] = 0;
                state = previous_state;
                previous_state = MESSAGE;
                message_being_displayed->destroy(message_being_displayed);
                message_being_displayed = NULL;
            }
            break;
*/
        case BATTLE:
            if (NULL == current_ba)
                current_ba = CREATE_BA(previous_state, ROLL, party, letters, hand);
            if (NULL != current_ba && state == BATTLE)
                current_ba->update(current_ba);
            if (NULL != current_ba && previous_state == BATTLE)
            {
                current_ba->destroy(current_ba);
                for (i = 0; i < NUM_CHARACTERS; i++)
                {
                    party[i]->current_state = waiting;
                }

                current_ba = NULL;
            }
            break;
        default:
            break;
        }
        TICKS++;
        FRAMES_RENDERED++;
        delay();
        reset_timer();
    }
    for (i = 0; i < 1; i++)
    {
        fprintf(data, "%s", party[i]->get_data(party[i]));
    }
    fclose(data);
    menu_transition(&menu->delay, renderer);
    SDL_WaitThread(hand_thread, NULL);

    dark_forest->destroy(dark_forest);
    hero->destroy(hero);
    menu->destroy(menu);
    hand->destroy(hand);
    save_bag(bag, 0);
    bag->destroy(bag);
    letters->destroy(letters);
    free(STAT_MATRIX);
    party[0]->destroy_party(party);
    SDL_DestroyRenderer(renderer);
    SDL_Delay(400);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void set_fullscreen(struct SDL_Window *window, Hero *hero)
{
    if (FULLSCREEN_ON)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0);
    }
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
int confirm(int val)
{
    if (!val)
        return 0;
    key_state[KEY] = 0;
    return 1;
}

int UP()
{
    return confirm(key_state[W]);
}
int LEFT()
{
    return confirm(key_state[A]);
}
int RIGHT()
{
    return confirm(key_state[D]);
}
int DOWN()
{
    return confirm(key_state[S]);
}
int CONFIRM()
{
    return confirm(key_state[J]);
}
int CANCEL()
{
    return confirm(key_state[L]);
}
int EXIT()
{
    return confirm(key_state[O]);
}
int FULL()
{
    return confirm(key_state[F]);
}
