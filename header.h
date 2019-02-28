//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_HEADER_H
#define JRPG_HEADER_H
#include <stdint.h>
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

#define FOREACH_ITEM(ITEM) \
    ITEM(POTION) \
    ITEM(ETHER) \
    ITEM(SOFT) \
    ITEM(PHOENIX_DOWN) \

#define FOREACH_STAT(STAT) \
    STAT(HP)  \
    STAT(MP)  \
    STAT(EXP) \

#define GERERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING)  #STRING,

enum ITEM_ENUM {    
    FOREACH_ITEM(GERERATE_ENUM)
};

static const char * ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)
};

enum STAT_ENUM {
    FOREACH_STAT(GERERATE_ENUM)
};

static const char * STATS[] = {
    FOREACH_STAT(GENERATE_STRING)
};

extern int NUM_STATS;
extern char **STAT_MATRIX;
extern int NUM_CHARACTERS;
extern int ITEM_QUANTITY;
extern int ITEMS_IN_BAG;
extern int * ITEM_QUANTITIES;
extern char **BAG;
extern int *BAG_QUANTITIES;
extern int inputs[6];
extern int EDGE_DETECTION[4];
extern int MOVEMENT_DISABLED;
extern int IS_MOVING;
extern int X;
extern int Y;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int TICK;
extern int REFRESH_ITEMS;

enum states
{
    DARK_FOREST,
    MAIN_MENU,
    ITEMS_MENU,
    USE_ITEM
};
enum states state, previous_state;
enum INPUTS
{
    NONE,
    OKAY,
    QUIT,
    CANCEL
};
enum INPUTS INPUT;

int FPS;
long double TIME_PER_TICK;
long double TIME_DELAY_PER_SECOND;
double DELTA;
uint64_t TIME_NOW;
uint64_t TIME_LAST;
uint64_t NANO_TIMER;
uint64_t TICKS_PER_SECOND;
int FRAMES_RENDERED;
void refresh_inputs(int *, int);
void set_items(int *);

#endif //JRPG_HEADER_H
