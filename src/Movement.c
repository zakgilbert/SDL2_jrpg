
#include "Movement.h"

int in_dungeon_state()
{
    int result = 0;

    switch (state)
    {
    case DARK_FOREST:
        result = 1;
        break;

    default:
        break;
    }
    return result;
}
int movement()
{
    int result = 0;
    if (!in_dungeon_state())
    {
        return result;
    }
    if (change_position())
    {
        bounds();
        result = 1;
    }
    return result;
}

int change_position()
{
    int is_moving = 0;

    if (!MOVEMENT_DISABLED)
    {
        if (key_state[SDL_SCANCODE_S])
        {
            Y--;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (key_state[SDL_SCANCODE_W])
        {
            Y++;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (key_state[SDL_SCANCODE_A])
        {
            X++;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (key_state[SDL_SCANCODE_D])
        {
            X--;
            is_moving = 1;
            NUM_STEPS++;
        }
    }
    return is_moving;
}

void bounds()
{
    if (X > 0)
    {
        X = 0;
    }
    if (X < -(MAP_WIDTH - (WINDOW_WIDTH / 2)))
    {
        X = -(MAP_WIDTH - (WINDOW_WIDTH / 2));
    }
    if (Y > 0)
    {
        Y = 0;
    }
    if (Y < -(MAP_HEIGHT - (WINDOW_HEIGHT / 2)))
    {
        Y = -(MAP_HEIGHT - (WINDOW_HEIGHT / 2));
    }
}