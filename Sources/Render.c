
/************************
 *  Render.c
*/

#include "Render.h"

render_function *buffer[50];
render_function *add_target(Target this, render_function *render_f)
{
    targets[NUM_TARGETS] = this;
    return render_f;
}
void add_target_function(render_function *target_function)
{
    buffer[NUM_TARGETS] = target_function;
    NUM_TARGETS++;
}
void render_buffer(struct SDL_Renderer *renderer)
{
    int i;

    for (i = 0; i < NUM_TARGETS; i++)
    {
        (*buffer[i])(targets[i], renderer);
        buffer[i] = NULL;
        targets[i] = NULL;
    }
    NUM_TARGETS = 0;
}
void render_forest_floor(void *obj, struct SDL_Renderer *renderer)
{
    Floor *this = (Floor *)obj;
    this->render_floor(this, renderer);
}
void render_forest_trees(void *obj, struct SDL_Renderer *renderer)
{
    Floor *this = (Floor *)obj;
    this->render_floor(this, renderer);
}
void render_hero(void *obj, struct SDL_Renderer *renderer)
{
    Hero *this = (Hero *)obj;
    this->render(this, renderer);
}