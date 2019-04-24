
/************************
	 *  Dialogue.c
	*/

#include "Dialogue.h"

static void _destroy(Dialogue *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static int _add_lines(Dialogue *this, Render_Q *q)
{
    int i, x, y, max, result;
    i = this->index;
    if (CONFIRM())
    {
        this->index++;
    }
    result = 0;
    x = this->x;
    y = this->y;
    if (this->num_lines <= 4)
    {
        if (i == this->num_lines)
        {
            result = 0;
            return result;
        }
        max = this->num_lines;
        result = 1;
    }
    else
    {
        if (i + 4 == this->num_lines)
        {
            max = this->num_lines;
            result = 1;
        }
        else if (i + 4 > this->num_lines)
        {
            result = 0;
            return result;
        }
        else
        {
            max = i + 4;
            result = 1;
        }
    }
    ENQUEUE(q, this->window, render_window, NULL);
    for (; i < max; i++)
    {
        ENQUEUE(q, CREATE_LINE(this->atlas, this->lines[i], x, y), render_line, destroy_line);
        y += 15;
    }
    return result;
}

Dialogue *CREATE_DIALOGUE(Atlas *atlas, const char **lines, int x, int y, int num_lines)
{
    Dialogue *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->add_lines = _add_lines;

    this->atlas = atlas;
    this->num_lines = num_lines;
    this->x = x;
    this->y = y;
    this->lines = lines;
    this->index = 0;
    this->window = CREATE_WINDOW(this->x - 8, this->y - 3, 208, 64);

    return this;
}
