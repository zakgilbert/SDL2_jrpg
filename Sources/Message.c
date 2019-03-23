#include "Message.h"
static void _destroy(Message *this)
{
    if (NULL != this)
    {
        SDL_DestroyTexture(this->texture);
        free(this);
        this = NULL;
    }
}
static int _render_dialogue(Message *this, struct SDL_Renderer *renderer)
{
    int is_finished, skip;
    size_t i;

    is_finished = 0;
    this->font = TTF_OpenFont(this->path, this->font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    TTF_SizeText(this->font, this->dialogue[0], &this->rect.w, &this->rect.h);
    skip = TTF_FontLineSkip(this->font);
    this->rect.y = skip;
    this->rect.x = (WINDOW_WIDTH / 2) - (200 / 2);
    this->message_background = CREATE_WINDOW(this->rect.x, 250, 225, skip * 5);
    this->rect.x = this->message_background->rect.x + 6;
    this->rect.y = this->message_background->rect.y + 6;

    this->message_background->render(this->message_background, renderer);
    this->current_line++;
    if (this->current_line > this->num_lines)
    {
        is_finished = 1;
    }
    else
    {
        is_finished = 0;
        if (this->current_line > 4)
        {
            i = this->current_line - 4;
        }
        else
        {
            i = 0;
        }

        for (; i < this->current_line; i++)
        {
            TTF_SizeText(this->font, this->dialogue[i], &this->rect.w, &this->rect.h);
            this->surface = TTF_RenderText_Solid(this->font, this->dialogue[i], WHITE);

            this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
            SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
            this->rect.y += skip;
        }
    }

    return is_finished;
}
static void _render_one_liner(Message *this, SDL_Renderer *renderer)
{
    this->font = TTF_OpenFont(this->path, this->font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    TTF_SizeText(this->font, this->message, &this->rect.w, &this->rect.h);

    if (this->rect.x == 0)
    {
        this->rect.x = (WINDOW_WIDTH / 2) - (this->rect.w / 2);
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
Message *CREATE_MESSAGE(char *message, int x, int y, int font_size, int type, int key)
{
    Message *this = malloc(sizeof(*this));

    this->destroy = _destroy;

    this->message = message;
    this->render_one_liner = _render_one_liner;
    this->render_dialogue = _render_dialogue;
    this->font = NULL;
    this->frames_of_existence = 3;
    this->texture = NULL;
    this->surface = NULL;
    this->rect.x = x;
    this->rect.y = y;
    if (type == DIALOGUE)
    {
        this->dialogue = DIALOGUES[key]->list;
        this->num_lines = DIALOGUES[key]->num_items;
    }

    this->path = "ponde___.ttf";
    this->number_of_characters = strlen(message);

    this->font_size = font_size;
    this->characters_rendered = 0;
    this->num_words = 0;
    this->type = type;
    this->current_line = 0;

    return this;
}