
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
    while (SDL_WaitEvent(&ev) && !EXIT())
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            key_state[O] = 1;
            break;

        case SDL_KEYDOWN:
            switch (ev.key.keysym.scancode)
            {
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                KEY = S;
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                KEY = W;
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                KEY = A;
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                KEY = D;
                continue;
            case SDL_SCANCODE_J:
                KEY = J;
                continue;
            case SDL_SCANCODE_L:
                KEY = L;
                continue;
            default:
                continue;
            }
            continue;
        case SDL_KEYUP:
            KEY = NON;
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
                continue;
            case SDL_SCANCODE_L:
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
