
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

    /* on left */
    if (EDGE_DETECTION[0])
    {
        USER_INPUTS[2] = 0;
    }
    /* on right */
    else if (EDGE_DETECTION[1])
    {
        USER_INPUTS[3] = 0;
    }
    /* on up */
    else if (EDGE_DETECTION[2])
    { 
        USER_INPUTS[1] = 0;
    }
    /* on down */
    else if (EDGE_DETECTION[3])
    { 
        USER_INPUTS[0] = 0;
    }
    if (!MOVEMENT_DISABLED)
    {
        if (USER_INPUTS[0])
        { 
            Y--;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[1])
        { 
            Y++;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[2])
        { 
            X++;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[3])
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
        EDGE_DETECTION[0] = 1;
        X = 0;
    }
    if (X < -(MAP_WIDTH - (WINDOW_WIDTH / 2)))
    {
        X = -(MAP_WIDTH - (WINDOW_WIDTH / 2));
        EDGE_DETECTION[1] = 1;
    }
    if (Y > 0)
    {
        Y = 0;
        EDGE_DETECTION[2] = 1;
    }
    if (Y < -(MAP_HEIGHT - (WINDOW_HEIGHT / 2)))
    {
        Y = -(MAP_HEIGHT - (WINDOW_HEIGHT / 2));
        EDGE_DETECTION[3] = 1;
    }
}