
/************************
	 *  Animation.c
	*/

#include "Animation.h"

#include "Character.h"
static const char *generic_hash_strings[] = {
    FOREACH_GENERIC_HASHTARGET(GENERATE_STRING)};

static void _destroy(Animation *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
Animation *CREATE_ANIMATION(struct SDL_Renderer *renderer)
{
    Animation *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->charge_spell = CREATE_SPRITE("Charge_Spell", "graphics/animation/charge_spell.png", 1, 10, renderer, 11, generic_hash_strings, 46, 46);
    return this;
}
