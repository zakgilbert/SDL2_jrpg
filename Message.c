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

static void _render(Message *this, const char *str, int x, int y, int w, int h, int font_size, int has_background)
{
    char font_path[] = "ponde___.ttf";
    const char main_menu_options[7][7] = {
        {"Items"},
        {"Skills"},
        {"Magic"},
        {"Status"},
        {"Config"},
        {"Save"},
        {"Exit"}};
    this->font = TTF_OpenFont(font_path, font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    this->skip = TTF_FontLineSkip(this->font) + 6;
    this->rect.x = 270;
    this->rect.y = 15;
}

static int _create_lines(Message *this)
{
    int i, k;
    k = 0;
    char *buffer = malloc(sizeof(char));
    this->message_2d = (char *)malloc(sizeof(char *) * 2);

    this->font = TTF_OpenFont(this->path, this->font_size);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    printf("\nmessage : %s", this->message);
    putchar('\n');
    for (i = 0; i < this->number_of_characters; i++)
    {
        if (this->message[i] == ' ')
        {
            buffer[k] = '\0';
            k = 0;
            i++;
            this->num_words++;
            this->message_2d = realloc(this->message_2d, sizeof(char *) * (this->num_words + 1));
            this->message_2d[this->num_words] = (char *)malloc(strlen(buffer));
            printf("\nAdding \"%s\" to line matrix", buffer);
            strcpy(this->message_2d[this->num_words - 1], buffer);
            printf("\nAdded \"%s\" to line matrix", this->message_2d[this->num_words - 1]);
            buffer = realloc(buffer, sizeof(char) + 1);
        }
        buffer = realloc(buffer, sizeof(char) * (k + 1));
        buffer[k] = this->message[i];
        k++;

       // TTF_SizeText(this->font, &l, &this->letter_width, &this->letter_height);
    }

    TTF_CloseFont(this->font);
}

Message *CREATE_MESSAGE(char *path, const char *message, int seconds_of_existence, int x, int y, int w, int h, int font_size)
{
    Message *this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->render = _render;
    this->create_lines = _create_lines;

    this->message_background = CREATE_WINDOW(x, y, w, h);
    this->message = message;
    this->font = NULL;

    this->texture = NULL;
    this->surface = NULL;

    this->path = path;
    this->seconds_of_existence = seconds_of_existence;
    this->frames_of_existence = seconds_of_existence * FPS;

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;

    this->number_of_characters = strlen(message);

    this->font_size = font_size;
    this->characters_rendered = 0;
    this->num_words = 0;

    return this;
}