
/************************
	 *  Sprite.c
	*/

#include "Sprite.h"

static void _destroy(Sprite *this)
{
    if (NULL != this)
    {
        free(this);
        this = NULL;
    }
}
static int check_row(int x, int y, int cols, int w, int h)
{
    if (x > (cols * w) - w)
        return 1;
    return 0;
}
/**
 * Hash Function Helper
 */
static int hash_code_helper(const char *key, const int prim, const int size)
{
    long hash = 0;
    int i;
    const int len = strlen(key);
    for (i = 0; i < len; i++)
    {
        hash += (long)pow(prim, len - (i + 1)) * key[i];
        hash = hash % size;
    }
    return (int)hash;
}

/**
 * Hash function
 */
static int hash_code(const char *key, const int num, const int attempt)
{
    int hash_a = hash_code_helper(key, PRIME_1, num);
    int hash_b = hash_code_helper(key, PRIME_2, num);
    return (hash_a + (attempt * (hash_b + 1))) % num;
}

/**
 * New Sprite Node
 */
static struct Sprite_Node *new_node(const char *key, int x, int y, int w, int h)
{
    struct Sprite_Node *node = malloc(sizeof(struct Sprite_Node));
    node->key = strdup(key);
    set_rect(&node->rect, x, y, w, h);
    return node;
}

/**
 * Insert
 */
static void _insert(Sprite *this, const char *key, int x, int y, int w, int h)
{
    struct Sprite_Node *node = new_node(key, x, y, w, h);
    int index = hash_code(node->key, this->size, 0);
    struct Sprite_Node *current_node = this->table[index];
    int i = 1;
    while (NULL != current_node)
    {
        index = hash_code(node->key, this->size, i);
        current_node = this->table[index];
        i++;
    }
    /**
        printf("%s was added at index %d\n", node->key, index);
*/
    this->table[index] = node;
}

/**
 * Search
 */
static Rect *_search(Sprite *this, const char *key)
{
    int index = hash_code(key, this->size, 0);
    struct Sprite_Node *disco = this->table[index];
    int i = 1;
    while (NULL != disco)
    {
        if (strcmp(disco->key, key) == 0)
        {
            this->frame.x = disco->rect.x;
            this->frame.y = disco->rect.y;
            /**
                printf("key %s was found at index %d\n", key, index);
*/
            return &this->frame;
        }
        index = hash_code(disco->key, this->size, i);
        i++;
    }
    printf("key %s was not found\n", key);
    return &this->frame;
}

static void _map(Sprite *this, const char *keys[], int num_keys)
{
    int i, x, y;
    x = 0;
    y = 0;
    for (i = 0; i < num_keys; i++)
    {
        if (check_row(x, y, this->cols, this->w, this->h))
        {
            x = 0;
            y += this->h;
        }
        /*
            printf("inserting %s  X: %d   Y: %d\n", keys[i], x, y);
*/
        this->insert(this, keys[i], x, y, this->w, this->h);
        x += this->w;
    }
}
/**
 * Create
 */
Sprite *CREATE_SPRITE(const char *name, const char *path,
                      int rows, int cols, Renderer renderer,
                      int argc, const char *argv[], int w, int h)
{
    Sprite *this = malloc(sizeof(*this));
    this->num_frames = rows * cols;
    this->size = 127;
    this->table = calloc(this->size, sizeof(struct Sprite_Node *));
    this->destroy = _destroy;
    this->search = _search;
    this->insert = _insert;
    this->map = _map;
    this->texture = create_texture(renderer, path, &this->frame);
    this->w = w;
    this->h = h;
    this->rows = rows;
    this->cols = cols;
    this->name = name;
    this->path = path;
    this->pos.w = w;
    this->pos.h = h;
    this->frame.x = 0;
    this->frame.y = 0;
    this->frame.w = w;
    this->frame.h = h;
    this->map(this, argv, argc);
    printf("creating Sprite %s\n", this->name);

    return this;
}
