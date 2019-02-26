//
// Created by zachary on 1/24/19.
//

#ifndef JRPG_HEADER_H
#define JRPG_HEADER_H
#include <stdint.h>
#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)

extern int NUM_CHARACTERS;
extern int ITEM_QUANTITY;
extern int ITEMS_IN_BAG;
extern int * ITEM_QUANTITIES;
extern char ** BAG;
extern int * BAG_QUANTITIES;
extern int inputs[6];
extern int EDGE_DETECTION[4];
extern int MOVEMENT_DISABLED;
extern int IS_MOVING;
extern int X;
extern int Y;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int TICK;

enum states{DARK_FOREST, MAIN_MENU, ITEMS_MENU};
enum states state, previous_state;
enum INPUTS{NONE, OKAY, QUIT, CANCEL};
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
