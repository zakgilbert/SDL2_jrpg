#include "Message.h"
static void _destroy(Message *this)
{
    if (NULL != this)
    {
        SDL_DestroyTexture(this->texture);
        free(this->message);
        free(this);
        this = NULL;
    }
}

static void _render_one_liner(Message *this, SDL_Renderer *renderer)
{
    this->font = TTF_OpenFont(this->path, this->font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    TTF_SizeText(this->font, this->message, &this->rect.w, &this->rect.h);
    
    if(this->rect.x == 0)
    {
        this->rect.x = (WINDOW_WIDTH / 2) - ( this->rect.w / 2 );
    }

    this->message_background = CREATE_WINDOW(this->rect.x, this->rect.y, this->rect.w + 15, this->rect.h + 15);
    this->rect.x = this->message_background->rect.x + 6;
    this->rect.y = this->message_background->rect.y + 6;

    this->message_background->render(this->message_background, renderer);
    this->surface = TTF_RenderText_Solid(this->font, this->message, WHITE);

    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
    TTF_CloseFont(this->font);
}
Message *CREATE_MESSAGE(char *message, int x, int y, int font_size)
{
    Message *this = malloc(sizeof(*this));

    this->destroy = _destroy;

    this->message = message;
    this->render_one_liner = _render_one_liner;
    this->font = NULL;

    this->texture = NULL;
    this->surface = NULL;
    this->rect.x = x;
    this->rect.y = y;

    this->path = "ponde___.ttf";
    this->number_of_characters = strlen(message);

    this->font_size = font_size;
    this->characters_rendered = 0;
    this->num_words = 0;
    this->num_lines = 0;

    return this;
}