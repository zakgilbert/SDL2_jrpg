//
// Created by zachary on 1/24/19.
//

#include "Movement.h"

int movement()
{
    int result = 0;
    if (state == MAIN_MENU)
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

    if (EDGE_DETECTION[0])
    { //on left
        inputs[2] = 0;
    }
    if (EDGE_DETECTION[1])
    { //on right
        inputs[3] = 0;
    }
    if (EDGE_DETECTION[2])
    { //on up
        inputs[1] = 0;
    }
    if (EDGE_DETECTION[3])
    { //on down
        inputs[0] = 0;
    }
    if (!MOVEMENT_DISABLED)
    {

        if (inputs[0])
        { //down
            Y++;
            is_moving = 1;
        }
        else if (inputs[1])
        { //up
            Y--;
            is_moving = 1;
        }
        else if (inputs[2])
        { //left
            X--;
            is_moving = 1;
        }
        else if (inputs[3])
        { //right
            X++;
            is_moving = 1;
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