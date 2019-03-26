//
// Created by zachary on 1/24/19.
//

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
       // printf("\nX: %d\nY: %d", X, Y);
        bounds();
        result = 1;
    }
    return result;
}

int change_position()
{
    int is_moving = 0;

    if (EDGE_DETECTION[0])
    { //on left
        USER_INPUTS[2] = 0;
    }
    else if (EDGE_DETECTION[1])
    { //on right
        USER_INPUTS[3] = 0;
    }
    else if (EDGE_DETECTION[2])
    { //on up
        USER_INPUTS[1] = 0;
    }
    else if (EDGE_DETECTION[3])
    { //on down
        USER_INPUTS[0] = 0;
    }
    if (!MOVEMENT_DISABLED)
    {
        if (USER_INPUTS[0])
        { //down
            Y++;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[1])
        { //up
            Y--;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[2])
        { //left
            X--;
            is_moving = 1;
            NUM_STEPS++;
        }
        else if (USER_INPUTS[3])
        { //right
            X++;
            is_moving = 1;
            NUM_STEPS++;
        }
    }
    return is_moving;
}

void bounds()
{
    if (X < 0)
    {
        EDGE_DETECTION[0] = 1;
        X = 0;
    }
    if (X > (MAP_WIDTH - WINDOW_WIDTH))
    {
        X = (MAP_WIDTH - WINDOW_WIDTH);
        EDGE_DETECTION[1] = 1;
    }
    if (Y < 0)
    {
        Y = 0;
        EDGE_DETECTION[2] = 1;
    }
    if (Y > (MAP_HEIGHT - WINDOW_HEIGHT))
    {
        Y = (MAP_HEIGHT - WINDOW_HEIGHT);
        EDGE_DETECTION[3] = 1;
    }
}