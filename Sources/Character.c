/* Character.c */

#include "Character.h"

static void __destroy(Character *this)
{
    SDL_DestroyTexture(this->character_texture);
    this->character_texture = NULL;

    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}

static void __destroy_party(Character **party)
{
    int i;

    for (i = 0; i < NUM_CHARACTERS; i++)
    {
        party[i]->destroy(party[i]);
    }
    free(party);
    party = NULL;
}

static int _update_party_stats(Character **these)
{
    for (size_t i = 0; i < NUM_CHARACTERS; i++)
    {
        these[i]->check_stats(these[i]);
    }
    return 0;
}

static void __create_character_texture(Character *this, struct SDL_Renderer *renderer)
{
    struct SDL_Surface *surface = NULL;
    struct SDL_Texture *texture = NULL;
    surface = IMG_Load(this->image_path);

    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &this->character_rect.w, &this->character_rect.h);
    this->character_texture = texture;
}
static void __check_stats(Character *this)
{
    sprintf(this->HP.str_current, "%d", this->HP.current);
    sprintf(this->MP.str_current, "%d", this->MP.current);
    sprintf(this->EXP.str_current, "%d", this->EXP.current);
    strcat(strcat(strcat(strcpy(this->HP.display, this->HP.name), this->HP.str_current), "/"), this->HP.str_max);
    strcat(strcat(strcat(strcpy(this->MP.display, this->MP.name), this->MP.str_current), "/"), this->MP.str_max);
    strcat(strcat(strcat(strcpy(this->EXP.display, this->EXP.name), this->EXP.str_current), "/"), this->EXP.str_max);
}
static void __create_battle_textures(Character *this, struct SDL_Renderer *renderer)
{
    this->textures_party = malloc(sizeof(struct SDL_Texture *) * NUM_CHARACTERS);
    for (size_t k = 0; k < NUM_CHARACTERS; k++)
    {
        this->textures_party[k] = create_texture(renderer, BATTLE_CHARACTER_GRAPHICS->list[k], &this->party_rect_2);
    }
    this->party_rect_1.x = 240;
    this->party_rect_1.y = 90;
    this->party_rect_2.x = 0;
    this->party_rect_2.y = 0;
    this->party_rect_1.w = SPRITE_FRAME_WIDTH;
    this->party_rect_1.h = SPRITE_FRAME_HEIGHT;
    this->party_rect_2.w = SPRITE_FRAME_WIDTH;
    this->party_rect_2.h = SPRITE_FRAME_HEIGHT;
}
static void __render_battle_textures(Character *this, struct SDL_Renderer *renderer)
{
    int party_x, party_y;
    party_x = this->party_rect_1.x;
    party_y = this->party_rect_1.y;

    for (size_t k = 0; k < NUM_CHARACTERS; k++)
    {
        SDL_RenderCopy(renderer, this->textures_party[k], &this->party_rect_2, &this->party_rect_1);
        this->party_rect_1.x += 15;
        this->party_rect_1.y += 30;
    }
    this->party_rect_1.x = party_x;
    this->party_rect_1.y = party_y;
}
static void __set_stats(Character *this, const char *name, const char *age, char *job, int HP, int MP, int EXP, const char *image_path)
{
    this->name = name;
    this->age = age;
    this->job = job;

    this->HP.current = HP;
    this->HP.max = HP;

    this->MP.current = MP;
    this->MP.max = MP;

    this->EXP.current = EXP;
    this->EXP.max = EXP;

    sprintf(this->EXP.str_max, "%d", this->EXP.max);
    sprintf(this->MP.str_max, "%d", this->MP.max);
    sprintf(this->HP.str_max, "%d", this->HP.max);
    this->image_path = image_path;
}

Character *CREATE_CHARACTER(int key)
{
    Character *this = (Character *)malloc(sizeof(*this));

    this->set_stats = __set_stats;
    this->destroy = __destroy;
    this->check_stats = __check_stats;
    this->create_character_texture = __create_character_texture;
    this->destroy_party = __destroy_party;
    this->update_party_stats = _update_party_stats;
    this->create_battle_textures = __create_battle_textures;
    this->render_battle_textures = __render_battle_textures;
    this->key = key;
    this->num_stats = 1;
    this->in_action_queue = 0;
    this->type = PARTY_MEMBER;
    strcpy(this->HP.name, "HP: ");
    strcpy(this->MP.name, "MP: ");
    strcpy(this->EXP.name, "EXP:");

    return this;
}