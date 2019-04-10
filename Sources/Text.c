
/************************
	 *  Text.c
	*/

#include "Text.h"

static void _destroy(Text *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static void _render(Text *this, struct SDL_Renderer *renderer)
{
    this->font = TTF_OpenFont(this->path, this->size);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    TTF_SizeText(this->font, this->text, &this->rect.w, &this->rect.h);
    SDL_RenderCopy(renderer,
                   SDL_CreateTextureFromSurface(renderer,
                                                TTF_RenderText_Solid(this->font, this->text, this->color)),
                   NULL, &this->rect);
    TTF_CloseFont(this->font);
}
Text *CREATE_TEXT(int x, int y, SDL_Color color, const char *path, int size, const char *text)
{
    Text *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->rect.x = x;
    this->rect.y = y;
    this->color = color;
    this->text = text;
    this->size = size;
    this->path = path;
    this->font = NULL;
    return this;
}

void render_text(void *obj, struct SDL_Renderer *renderer)
{
    Text *this = (Text *)obj;
    this->render(this, renderer);
}