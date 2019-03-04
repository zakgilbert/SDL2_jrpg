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

static void _render(Message *this, SDL_Renderer *renderer, int has_background)
{
    int skip, i;
    this->font = TTF_OpenFont(this->path, this->font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }

    skip = TTF_FontLineSkip(this->font);
    if (!has_background)
    {
        this->message_background->destroy(this->message_background);
    }
    this->message_background->render(this->message_background, renderer);
    for (i = 0; i <= this->current_line && this->current_line <= this->num_lines; i++)
    {
        TTF_SizeText(this->font, this->message_2d[i], &this->rect.w, &this->rect.h);
        this->surface = TTF_RenderText_Solid(this->font, this->message_2d[i], WHITE);

        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
        SDL_FreeSurface(this->surface);
        this->rect.y += skip;
    }
    SDL_DestroyTexture(this->texture);
    this->current_line++;
    TTF_CloseFont(this->font);
}

static int _create_lines(Message *this)
{
    int i, k, f, space_width, space_height;
    int current_line_width, trash_h;
    int current_word_width, current_num_words;
    int current_characters_in_line;

    char space = ' ';
    char *space_str = " ";
    f = 0;
    current_line_width = 0;
    current_characters_in_line = 0;
    current_num_words = 0;
    trash_h = 0;
    current_word_width = 0;
    k = 0;
    space_width = 0;
    space_height = 0;

    char *buffer = malloc(sizeof(char));
    char **temp_2d = (char **)malloc(sizeof(char *) * 2);

    this->font = TTF_OpenFont(this->path, this->font_size);
    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    printf("\nmessage : %s", this->message);
    TTF_SizeText(this->font, space_str, &space_width, &space_height);
    for (i = 0; i < this->number_of_characters; i++)
    {
        if (this->message[i] == ' ')
        {
            buffer[k] = '\0';
            k = 0;
            i++;
            this->num_words++;
            temp_2d = realloc(temp_2d, sizeof(char *) * (this->num_words + 1));
            temp_2d[this->num_words] = (char *)malloc(strlen(buffer) + strlen(space_str));
            strcpy(temp_2d[this->num_words - 1], buffer);
            strcat(temp_2d[this->num_words - 1], space_str);
            printf("\nAdded \"%s\" to line matrix", temp_2d[this->num_words - 1]);
            buffer = realloc(buffer, sizeof(char) + 1);
        }
        buffer = realloc(buffer, sizeof(char) * (k + 1));
        buffer[k] = this->message[i];
        current_characters_in_line++;
        k++;
    }

    free(buffer);
    for (k = 0; k < this->num_words; k++)
    {
        printf("\n%s", temp_2d[k]);
    }
    int *lines = malloc(sizeof(int));
    for (k = 0; k < this->num_words; k++)
    {
        TTF_SizeText(this->font, temp_2d[k], &current_word_width, &trash_h);
        current_line_width += current_word_width;
        if (current_line_width > this->message_background->rect.w)
        {
            lines[this->num_lines] = k;
            this->num_lines++;
            lines = realloc(lines, (sizeof(int) * this->num_lines) + 1);
            printf("\nLine %d ends at the %dth word.", this->num_lines - 1, k);
            current_line_width = 0;
        }
    }
    this->message_2d = (char **)malloc(sizeof(char *) * (this->num_lines));
    this->message_2d[0] = (char *)malloc(100);

    strncpy(this->message_2d[0], temp_2d[0], strlen(temp_2d[0]));
    strcpy(this->message_2d[0], temp_2d[0]);
    int j = 0;
    for (k = 1; k <= this->num_words; k++)
    {
        printf("\nSize of \"%s\" on the %dth line is %d", this->message_2d[j], j, strlen(this->message_2d[j]));
        if (k + 1 == lines[j])
        {
            strcat(this->message_2d[j], temp_2d[k]);
            j++;
            this->message_2d[j] = (char *)malloc(100);
            k++;
            strcpy(this->message_2d[j], temp_2d[k]);
        }
        else
        {
            ///      strncat(this->message_2d[j], temp_2d[k], strlen(temp_2d[k]));
            strcat(this->message_2d[j], temp_2d[k]);
        }
    }
    this->message_2d[this->num_lines][strlen(this->message_2d[this->num_lines]) - 1] = '\0';
    for (k = 0; k < this->num_words; k++)
    {
        // free(temp_2d[k]);
    }
    for (k = 0; k <= this->num_lines; k++)
    {
        printf("\nline %d is %d bytes", k, strlen(this->message_2d[k]));
        printf("\n%s", this->message_2d[k]);
    }
    free(lines);
    TTF_CloseFont(this->font);
}
static void _render_one_liner(Message *this, SDL_Renderer *renderer)
{
    this->font = TTF_OpenFont(this->path, this->font_size);

    if (!this->font)
    {
        printf("In function: create_Main_Menu_Options---TTF_OpenFont: %s\n", TTF_GetError());
    }
    TTF_SizeText(this->font, this->message, &this->rect.w, &this->rect.h);

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
Message *ONE_LINER(char *path, const char *message, int seconds_of_existence, int x, int y, int font_size)
{
    Message *this = malloc(sizeof(*this));

    this->destroy = _destroy;

    this->message = message;
    this->render_one_liner = _render_one_liner;
    this->render = _render;
    this->font = NULL;

    this->texture = NULL;
    this->surface = NULL;
    this->rect.x = x;
    this->rect.y = y;

    this->path = path;
    this->seconds_of_existence = seconds_of_existence;
    this->frames_of_existence = seconds_of_existence * FPS;
    this->number_of_characters = strlen(message);

    this->font_size = font_size;
    this->characters_rendered = 0;
    this->num_words = 0;
    this->num_lines = 0;

    return this;
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

    this->message_background->rect.x = x;
    this->message_background->rect.y = y;
    this->message_background->rect.w = w;
    this->message_background->rect.h = h;

    this->rect.x = x + 30;
    this->rect.y = y + 30;

    printf("\nrect width: %d", this->rect.w);
    this->number_of_characters = strlen(message);

    this->font_size = font_size;
    this->characters_rendered = 0;
    this->num_words = 0;
    this->num_lines = 0;
    this->current_line = 0;

    return this;
}