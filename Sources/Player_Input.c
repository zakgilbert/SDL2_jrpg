
#include "Player_Input.h"

int wait_for_okay()
{
    MOVEMENT_DISABLED = 1;
    while (!USER_INPUTS[4])
    {
        SDL_Delay(1);
    }
    MOVEMENT_DISABLED = 0;
    return 0;
}

int input_handler(void *data)
{
    union SDL_Event ev;

    while (SDL_WaitEvent(&ev) && INPUT != QUIT)
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            INPUT = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (ev.key.keysym.scancode)
            {
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                continue;
            case SDL_SCANCODE_J:
                INPUT = OKAY;
                continue;
            case SDL_SCANCODE_L:
                INPUT = CANCEL;
                continue;
            default:
                continue;
            }
            continue;
        case SDL_KEYUP:
            switch (ev.key.keysym.scancode)
            {
            case SDL_SCANCODE_O:
                INPUT = QUIT;
                continue;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                continue;
            case SDL_SCANCODE_J:
                INPUT = NONE;
                continue;
            case SDL_SCANCODE_L:
                INPUT = NONE;
                continue;
            case SDL_SCANCODE_F:
                FULLSCREEN_ON = !(FULLSCREEN_ON);
                continue;
            default:
                break;
            }
        default:
            break;
        }
    }
    return 0;
}
