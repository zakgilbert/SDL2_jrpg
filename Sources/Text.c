
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
    TTF_SizeText(this->font, this->text, &this->rect.w, &this->rect.h);
    SDL_RenderCopy(renderer,
                   SDL_CreateTextureFromSurface(renderer,
                                                TTF_RenderText_Solid(this->font, this->text, this->color)),
                   NULL, &this->rect);
}
Text *CREATE_TEXT(int x, int y, SDL_Color color, TTF_Font *font, const char *text)
{
    Text *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->rect.x = x;
    this->rect.y = y;
    this->color = color;
    this->text = text;
    this->font = font;
    return this;
}

void render_text(void *obj, struct SDL_Renderer *renderer)
{
    Text *this = (Text *)obj;
    this->render(this, renderer);
}
void text_destroy(void *obj)
{
    Text *this = (Text *)obj;
    this->destroy(this);
}

void close_font(void *obj, struct SDL_Renderer *renderer)
{
    TTF_Font *this = (TTF_Font *)obj;
    printf("closingfont\n");
    TTF_CloseFont(this);
}