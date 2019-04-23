
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
static void _create_lines(Dialogue *this, Atlas *atlas)
{
    int i, longest_line;
    longest_line = 0;

    for (i = 0; i < this->num_lines; i++)
    {
        if ((int)(strlen(this->lines[i])) > longest_line)
            longest_line = (int)strlen(this->lines[i]);
    }
    this->window = CREATE_WINDOW(this->x - 8, this->y - 3, longest_line * 8, this->num_lines * 8);
}

static int _add_lines(Dialogue *this, Render_Q *q)
{
    int i, x, y, max;
    if (CONFIRM())
    {
        this->index++;
    }
    x = this->x;
    y = this->y;
    i = this->index;
    if (i + 4 == this->num_lines)
    {
        max = this->num_lines;
    }
    else if (i + 4 > this->num_lines)
    {
        return 0;
    }
    else
    {
        max = i + 4;
    }

    ENQUEUE(q, this->window, render_window, NULL);

    for (; i < max; i++)
    {
        ;
        ENQUEUE(q, CREATE_LINE(this->atlas, this->lines[i], x, y), render_line0, destroy_line);
        y += 15;
    }
    return 1;
}

Dialogue *CREATE_DIALOGUE(Atlas *atlas, const char **lines, int x, int y, int num_lines)
{
    Dialogue *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->add_lines = _add_lines;
    this->create_lines = _create_lines;

    this->atlas = atlas;
    this->num_lines = num_lines;
    this->x = x;
    this->y = y;
    this->lines = lines;
    this->index = 0;
    this->create_lines(this, atlas);

    return this;
}
