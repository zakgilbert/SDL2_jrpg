
/************************
	 *  Animation.c
	*/

#include "Animation.h"

static void _destroy(Animation *this)
{
    if (NULL != this)
    {
        free(this->magic_atk);
        free(this->magic_charge);
        free(this->slash);
        free(this);
        this = NULL;
    }
}
static struct Sprite_Packet *_new_sprite_packet(struct SDL_Renderer *renderer, const char *path, int rows, int cols)
{
    struct Sprite_Packet *packet = malloc(sizeof(struct Sprite_Packet));
    packet->texture = create_texture(renderer, path, &packet->rect_2);
    packet->rect_1.x = 150;
    packet->rect_1.y = 150;
    packet->rect_2.x = 0;
    packet->rect_2.y = 0;
    packet->w = packet->rect_2.w / cols;
    packet->h = packet->rect_2.h / rows;
    packet->rect_1.w = packet->w;
    packet->rect_1.h = packet->h;
    packet->rect_2.w = packet->w;
    packet->rect_2.h = packet->h;
    return packet;
}
static void _render_animation(void *obj, struct SDL_Renderer *renderer)
{
    struct Sprite_Packet *this = (struct Sprite_Packet *)obj;
    SDL_RenderCopy(renderer, this->texture, &this->rect_2, &this->rect_1);
}
static void _create_textures(Animation *this, struct SDL_Renderer *renderer)
{
    this->magic_atk[0] = this->new_sprite_packet(renderer, "graphics/animation/fire_1_sheet.png", 1, 5);
    this->magic_charge[0] = this->new_sprite_packet(renderer, "graphics/animation/fire_1_char.png", 1, 10);
    this->slash[0] = this->new_sprite_packet(renderer, "graphics/animation/weapon_fx_sheet.png", 1, 9);
}
Animation *CREATE_ANIMATION(struct SDL_Renderer *renderer)
{
    Animation *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->create_textures = _create_textures;
    this->new_sprite_packet = _new_sprite_packet;
    this->render_animation = _render_animation;

    this->magic_atk = malloc(sizeof(struct Animation_Packet *));
    this->magic_charge = malloc(sizeof(struct Animation_Packet *));
    this->slash = malloc(sizeof(struct Animation_Packet *));
    this->create_textures(this, renderer);
    return this;
}
